// C2GA
#include <c2ga/Mvec.hpp>

// C++ / OpenGL3
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <math.h>

// glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

// gar (Geaometric Algebra Raytracer)
#include <gar/Light.hpp>

using namespace c2ga;
using namespace gar;

static const int WIDTH = 500;
static const int HEIGHT = 500;

void drawLandmark() {
	float padding = 10.f;
	// Axe des abscisses rouge
	glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		glVertex2f(-WIDTH / 2.f + padding, 0);
		glVertex2f( WIDTH / 2.f - padding, 0);
	glEnd();
	// Axe des ordonnées vert
	glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		glVertex2f(0, -HEIGHT / 2.f + padding);
		glVertex2f(0,  HEIGHT / 2.f - padding);
	glEnd();
}

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

float easeIn(float t, float b, float c, float d) {
	return c*(t/d)*t + b;
}

template<typename T>
Mvec<T> point(const T &x, const T &y){

	Mvec<T> mv;
	mv[E1] = x;
	mv[E2] = y;
	mv[Ei] = 0.5 * mv.quadraticNorm();
	mv[E0] = 1.0;

	return mv;
}

template<typename T>
Mvec<T> line(const Mvec<T> &p1, const Mvec<T> &p2) {
	return p1 ^ ei<T>() ^ p2;
}

template<typename T>
Mvec<T> line(const T &a, const T &b, const T &c) {
	return a * e1<T>() + b * e2<T>() + c*ei<T>();
}

template<typename T>
Mvec<T> circle(const T &x, const T &y, const T &r) {
	return !(point(x, y) - (pow(r, 2)/2) * ei<T>());
}

template<typename T>
Mvec<T> projectPointOnCircle(const Mvec<T> &p, const Mvec<T> &c) {
	return (p ^ ei<T>()) < (c*c);
}

template<typename T>
void drawPoint(const Mvec<T> &p) {
	glVertex2f(p[E1], p[E2]);
}

template<typename T>
void drawLine(const Mvec<T> &p1, const Mvec<T> &p2) {
	glBegin(GL_LINES);
		glVertex2f(p1[E1], p1[E2]);
		glVertex2f(p2[E1], p2[E2]);
	glEnd();
}

template<typename T>
void DrawCircle(const Mvec<T> &center, float r, int num_segments = 64) {
	float cx = center[E1];
	float cy = center[E2];
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta); // Calculate the tangential factor
	float radial_factor = cosf(theta); // Calculate the radial factor
	float x = r; // We start at angle = 0
	float y = 0;

	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++)
	{
		glVertex2f(x + cx, y + cy); //output vertex

		// Calculate the tangential vector
		// Remember, the radial vector is (x, y)
		// To get the tangential vector we flip those coordinates and negate one of them
		float tx = -y;
		float ty = x;

		// Add the tangential vector
		x += tx * tangetial_factor;
		y += ty * tangetial_factor;

		// Correct using the radial factor
		x *= radial_factor;
		y *= radial_factor;
	}
	glEnd();
}

template<typename T>
float distance(const Mvec<T> &p1, const Mvec<T> &p2) {
	return sqrt(pow(p2[E1] - p1[E1], 2) + pow(p2[E2]-p1[E1], 2));
}

int main() {
	std::cout << "Lancement du programme..." << std::endl;

	// Initialize SDL and open a window
	glimac::SDLWindowManager windowManager(WIDTH, HEIGHT, "GA Raytracer");
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIDTH / 2.f, WIDTH / 2.f, -HEIGHT / 2.f, HEIGHT / 2.f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if (GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	glm::vec2 pixelPos;
	int padding = 0.f;

	// Light Setup
	Light mainLight(150.f, glm::vec2(20.f, 40.f));
	float ambientIntensity = 0.05f;

	// Add circle
	glm::vec2 circlePos(-50.f, 80.f);
	float circleRadius = 40.f;
	glm::vec2 circle2Pos(0.f, 0.f);
	float circle2Radius = 80.f;
	float circle3Radius = 80.f;

	Mvec<double> pt1 = point(10.0, 20.0);
	Mvec<double> pt2 = point(20.0, 50.0);
	Mvec<double> pt3 = point(50.0, 20.0);

	Mvec<double> line1 = pt1 ^ pt2 ^ ei<double>();
	Mvec<double> circle1 = pt1 ^ pt2 ^ pt3;
	Mvec<double> circle2 = circle(-100, 50, 80);
	Mvec<double> circle3 = circle(-120, 50, 80);
	Mvec<double> centroid = (pt1 + pt2 + pt3) / 3;
	Mvec<double> circum = -circle1 / (ei<double>() < circle1);
	Mvec<double> circum2 = -circle2 / (ei<double>() < circle2);
	Mvec<double> circum3 = -circle3 / (ei<double>() < circle3);

	// Normalize point
	// pt1 /= - pt1 | ei<double>(); // = composante en E0
	// pt2 /= - pt2 | ei<double>(); // = composante en E0
	// pt3 /= - pt3 | ei<double>(); // = composante en E0

	std::cout << "pt1 : " << pt1 << std::endl;
	std::cout << "line1 : " << line1 << std::endl;
	std::cout << "line1.grade() : " << line1.grade() << std::endl;
	std::cout << "circle1 : " << circle1 << std::endl;
	std::cout << "circle2 : " << circle2 << std::endl;
	std::cout << "centroid : " << centroid << std::endl;
	std::cout << "circum : " << circum << std::endl;
	std::cout << "circum2 : " << circum2 << std::endl;
	std::cout << "circum3 : " << circum3 << std::endl;

	std::cout << "circum.grade() : " << circum.grade() << std::endl;
	std::cout << "circum2.grade() : " << circum2.grade() << std::endl;

	Mvec<double> pt4 = point(0.0, 0.0);
	Mvec<double> pt5 = projectPointOnCircle(pt4, circle1);
	std::cout << "pt4 : " << pt4 << std::endl;
	std::cout << "pt5 : " << pt5 << std::endl;

	Mvec<double> a = point(-80, -80);
	Mvec<double> b = point(-80, -40);
	Mvec<double> c = point(-30, -20);
	Mvec<double> d = point(-20, -20);

	Mvec<double> l1 = line(a, b);
	Mvec<double> l2 = line(c, d);

	Mvec<double> intersection = l1 | l2;

	std::cout << "l1 : " << l1 << std::endl;
	std::cout << "l2 : " << l2 << std::endl;
	std::cout << "intersection : " << intersection << std::endl;

	Mvec<double> pp1 = circle1 / circle2;
	std::cout << "pp1 : " << pp1 << std::endl;
	std::cout << "pp1.grade() : " << pp1.grade() << std::endl;

	Mvec<double> pp2 = pt1 ^ pt2;
	std::cout << "pp2 : " << pp2 << std::endl;
	std::cout << "pp2.grade() : " << pp2.grade() << std::endl;
	std::cout << "pp2 dual : " << !pp2 << std::endl;
	std::cout << "pp2 dual grade : " << (!pp2).grade() << std::endl;

	Mvec<double> pp3 = l1 / circle2;
	std::cout << "pp3 : " << pp3 << std::endl;
	std::cout << "pp3.grade() : " << pp3.grade() << std::endl;

	Mvec<double> pp4_bis = circle2 * circle3;
	Mvec<double> pp4 = ((circle2 * Iinv<double>()) ^ (circle3*Iinv<double>())) * I<double>()  ;
	std::cout << "pp4 : " << pp4 << std::endl;
	std::cout << "pp4.grade() : " << pp4.grade() << std::endl;
	std::cout << "pp4_bis : " << pp4_bis << std::endl;
	std::cout << "pp4_bis.grade() : " << pp4_bis.grade() << std::endl;


	// Application loop:
	bool done = false;
	while (!done) {

		// Event loop:
		SDL_Event e;
		while (windowManager.pollEvent(e)) {
			switch (e.type) {
				case SDL_QUIT:
					done = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = true;
							break;
						case SDLK_KP_PLUS:
							mainLight.size() += 10.f;
							if (mainLight.size() > 500.f) {
								mainLight.size() = 500.f;
							}
							break;
						case SDLK_KP_MINUS:
							mainLight.size() -= 10.f;
							if (mainLight.size() < 0.f) {
								mainLight.size() = 0.f;
							}
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
						mainLight.pos() += glm::vec2(e.motion.xrel, -e.motion.yrel);
						pt1 = pt4 = point(mainLight.pos().x, mainLight.pos().y);
						break;
					}
				default:
					break;
			}
		}

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/

		// Clear canvas
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set point size (1 = 1px)
		glPointSize(5.f);

		circle1 = pt1 ^ pt2 ^ pt3;
		centroid = (pt1 + pt2 + pt3) / 3;
		circum = -circle1 / (ei<double>() < circle1);
		pt5 = projectPointOnCircle(pt4, circle1);
		circlePos.x = circum[E1];
		circlePos.y = circum[E2];
		circleRadius = distance(circum, pt1);
		circle2Pos.x = circum2[E1];
		circle2Pos.y = circum2[E2];
		pp1 = circle1 | circle2;
		// std::cout << "pp1 : " << pp1 << std::endl;
		pp2 = pt1 ^ pt2;


		// Compute canvas
		glBegin(GL_POINTS);
			for (int i = -WIDTH/2 + padding; i < WIDTH/2 - padding; i++) {
				for (int j = -HEIGHT/2 + padding; j < HEIGHT/2 - padding; j++) {

					// float distanceFromLight = sqrt((mainLight.pos().x - i) * (mainLight.pos().x - i) + (mainLight.pos().y - j) * (mainLight.pos().y - j));
					// if (distanceFromLight > mainLight.size()) {
					// 	// The pixel is too far from the light source
					// 	glColor3f(ambientIntensity, ambientIntensity, ambientIntensity);
					// } else {
					// 	// float intensity = lerp(ambientIntensity, 1., 1. - (distance / lightSize));
					// 	float intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), ambientIntensity, 1.f, 1.f);
					// 	glColor3f(intensity, intensity, intensity);
					// }

					float distanceFromCircle = sqrt((circlePos.x - i) * (circlePos.x - i) + (circlePos.y - j) * (circlePos.y - j));
					if (distanceFromCircle < circleRadius && distanceFromCircle > circleRadius - 2.f) {
						glColor3f(1., ambientIntensity, ambientIntensity);
					}

					distanceFromCircle = sqrt((circle2Pos.x - i) * (circle2Pos.x - i) + (circle2Pos.y - j) * (circle2Pos.y - j));
					if (distanceFromCircle < circle2Radius && distanceFromCircle > circle2Radius - 2.f) {
						glColor3f(ambientIntensity, 1., ambientIntensity);
					}

					// glVertex2f(i, j);
				}
			}

			// RED
			glColor3f(1.f, 0.f, 0.f);
			drawPoint(pt1);
			drawPoint(pt2);
			drawPoint(pt3);
			drawPoint(intersection);

			// BLUE
			glColor3f(0.f, 0.f, 1.f);
			drawPoint(centroid);
			drawPoint(a);
			drawPoint(b);
			glVertex2f(pp3[E01], pp3[E02]);

			// YELLOW
			// Point on light
			glColor3f(1.f, 1.f, 0.f);
			drawPoint(pt4);
			drawPoint(pt1*pt2);
			glVertex2f(pp2[E01], pp2[E02]);
			glVertex2f(pp4[E01], pp4[E02]);
			glVertex2f(pp1[E01], pp1[E02]);

			// GREEN
			glColor3f(0.f, 1.f, 0.f);
			// Light center projected on circle
			// drawPoint(pt5);
			drawPoint(circum);
			drawPoint(circum2);
			drawPoint(circum3);
			drawPoint(c);
			drawPoint(d);
			glVertex2f((!pp2)[E01], (!pp2)[E02]);
			glVertex2f((!pp4)[E01], (!pp4)[E02]);
		glEnd();

		glColor3f(0.f, 0.f, 1.f);
		drawLine(a, b);
		glColor3f(0.f, 1.f, 0.f);
		drawLine(c, d);

		DrawCircle(circum, circleRadius);
		DrawCircle(circum2, circle2Radius);
		DrawCircle(circum3, circle3Radius);

		drawLandmark();

		// Update the display
		windowManager.swapBuffers();
	}

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
