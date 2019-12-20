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

static const Mvec<double> NI = ei<double>();
static const Mvec<double> N0 = 0.5 * (ei<double>() - e0<double>());

void drawLandmark() {
	float padding = 10.f;
	// Axe des abscisses rouge
	glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex2f(-WIDTH / 2.f + padding, 0);
		glVertex2f( WIDTH / 2.f - padding, 0);
	glEnd();
	// Axe des ordonnées vert
	glBegin(GL_LINES);
		glColor3ub(0, 255, 0);
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

// Mvec<double> point(double x = 0.0, double y = 0.0) {
// 	return N0 + x*e1<double>() + y*e2<double>() + 0.5*(x*x+y*y)*NI;
// }

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
	return p1 ^ p2 ^ ei<T>();
}

template<typename T>
Mvec<T> circle(const T &x, const T &y, const T &r) {
	return !(point(x, y) - pow(r, 2/2*NI));
}

template<typename T>
Mvec<T> projectPointOnCircle(const Mvec<T> &p, const Mvec<T> &c) {
	return (p^NI) < c*c;
}

template<typename T>
void drawPoint(const Mvec<T> &p) {
	glVertex2f(p[E1], p[E2]);
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

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if (GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	// glDisable(GL_DEPTH_TEST);
	glm::vec2 pixelPos;
	int padding = 0.f;

	// Light Setup
	Light mainLight(150.f, glm::vec2(20.f, 40.f));
	float ambientIntensity = 0.05f;

	// Add circle
	glm::vec2 circlePos(-50.f, 80.f);
	float circleRadius = 40.f;

	Mvec<double> pt1 = point(10.0, 20.0);
	Mvec<double> pt2 = point(20.0, 50.0);
	Mvec<double> pt3 = point(50.0, 20.0);

	Mvec<double> line1 = pt1 ^ pt2 ^ ei<double>();
	Mvec<double> circle1 = pt1 ^ pt2 ^ pt3;
	Mvec<double> circle2 = circle(40.0, 60.0, 23.0);
	Mvec<double> centroid = (pt1 + pt2 + pt3) / 3;
	Mvec<double> circum = -circle1 / (ei<double>() < circle1);

	// Normalize point
	// pt1 /= - pt1 | ei<double>(); // = composante en E0
	// pt2 /= - pt2 | ei<double>(); // = composante en E0
	// pt3 /= - pt3 | ei<double>(); // = composante en E0

	std::cout << "NI : " << ei<double>() << std::endl;
	std::cout << "pt1 : " << pt1 << std::endl;
	std::cout << "line1 : " << line1 << std::endl;
	std::cout << "line1.grade() : " << line1.grade() << std::endl;
	std::cout << "circle1 : " << circle1 << std::endl;
	std::cout << "circle2 : " << circle2 << std::endl;
	std::cout << "circle1.grade() : " << circle1.grade() << std::endl;
	std::cout << "circle2.grade() : " << circle2.grade() << std::endl;
	std::cout << "centroid : " << centroid << std::endl;
	std::cout << "circum : " << circum << std::endl;

	Mvec<double> pt4 = point(0.0, 0.0);
	Mvec<double> pt5 = projectPointOnCircle(pt4, circle1);
	std::cout << "pt4 : " << pt4 << std::endl;
	std::cout << "pt5 : " << pt5 << std::endl;

	Mvec<double> a = point(-40, -40);
	Mvec<double> b = point(-40, -30);
	Mvec<double> c = point(-30, -20);
	Mvec<double> d = point(-20, -20);

	Mvec<double> l1 = line(a, b);
	Mvec<double> l2 = line(c, d);

	Mvec<double> intersection = l1 | l2;

	std::cout << "l1 : " << l1 << std::endl;
	std::cout << "l2 : " << l2 << std::endl;
	std::cout << "intersection : " << intersection << std::endl;

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

		// Compute canvas
		glBegin(GL_POINTS);
			for (int i = -WIDTH/2 + padding; i < WIDTH/2 - padding; i++) {
				for (int j = -HEIGHT/2 + padding; j < HEIGHT/2 - padding; j++) {

					float distanceFromLight = sqrt((mainLight.pos().x - i) * (mainLight.pos().x - i) + (mainLight.pos().y - j) * (mainLight.pos().y - j));
					if (distanceFromLight > mainLight.size()) {
						// The pixel is too far from the light source
						glColor3f(ambientIntensity, ambientIntensity, ambientIntensity);
					} else {
						// float intensity = lerp(ambientIntensity, 1., 1. - (distance / lightSize));
						float intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), ambientIntensity, 1.f, 1.f);
						glColor3f(intensity, intensity, intensity);
					}

					float distanceFromCircle = sqrt((circlePos.x - i) * (circlePos.x - i) + (circlePos.y - j) * (circlePos.y - j));
					if (distanceFromCircle < circleRadius && distanceFromCircle > circleRadius - 2.f) {
						glColor3f(1., ambientIntensity, ambientIntensity);
					}

					glVertex2f(i, j);
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

			// YELLOW
			// Point on light
			glColor3f(1.f, 1.f, 0.f);
			drawPoint(pt4);

			// GREEN
			// Light Center projected on circle
			glColor3f(0.f, 1.f, 0.f);
			drawPoint(pt5);
			drawPoint(circum);

			drawPoint(c);
			drawPoint(d);
		glEnd();

		drawLandmark();

		// Update the display
		windowManager.swapBuffers();
	}

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
