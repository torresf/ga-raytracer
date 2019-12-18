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

static const Mvec<double> NI = ei<double>() + e0<double>();
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

Mvec<double> point(double x = 0.0, double y = 0.0) {
	return N0 + x*e1<double>() + y*e2<double>() + 0.5*(x*x+y*y)*NI;
}

Mvec<double> line(double a = 0.0, double b = 0.0, double c = 0.0) {
	return a*e1<double>() + b*e2<double>() + c*NI;
}

Mvec<double> circle(double x = 0.0, double y = 0.0, double r = 10.0) {
	return !(point(x, y) - pow(r, 2/2*NI));
}

Mvec<double> projectPointOnCircle(Mvec<double> p, Mvec<double> c) {
	return (p^NI) < c*c;
}

int main() {
	std::cout << "Lancement du programme..." << std::endl;

	// Initialize SDL and open a window
	glimac::SDLWindowManager windowManager(WIDTH, HEIGHT, "GA Raytracer");
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIDTH / 2.f, WIDTH / 2.f, -HEIGHT / 2.f, HEIGHT / 2.f);
	// gluOrtho2D(-1.f, 1.f, -1.f, 1.f);

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

	double x1 = 10.0;
	double y1 = 20.0;

	double x2 = 20.0;
	double y2 = 50.0;

	double x3 = 50.0;
	double y3 = 20.0;

	// Mvec<double> pt1;
	// pt1[scalar] = 1.0;
	// pt1[E1] = 10.0;
	// pt1[E2] = 20.0;
	// pt1[Ei] = 0.5*(pt1[E1]*pt1[E1]+pt1[E2]*pt1[E2]);

	// Mvec<double> pt2;
	// pt2[scalar] = 1.0;
	// pt2[E1] = 20.0;
	// pt2[E2] = 50.0;
	// pt2[Ei] = 0.5*(pt2[E1]*pt2[E1]+pt2[E2]*pt2[E2]);

	// Mvec<double> pt3;
	// pt3[scalar] = 1.0;
	// pt3[E1] = 50.0;
	// pt3[E2] = 20.0;
	// pt3[Ei] = 0.5*(pt3[E1]*pt3[E1]+pt3[E2]*pt3[E2]);

	Mvec<double> pt1 = point(x1, y1);
	Mvec<double> pt2 = point(x2, y2);
	Mvec<double> pt3 = point(x3, y3);

	Mvec<double> l1 = line(0.0, 1.0, 0.0);
	Mvec<double> l2 = pt1 ^ pt2 ^ NI;

	Mvec<double> circle1 = pt1 ^ pt2 ^ pt3;
	Mvec<double> circle2 = (20.0*e1<double>()^e2<double>()^NI) + (5.0*N0^e1<double>()^e2<double>());
	Mvec<double> circle3 = circle(40.0, 60.0, 23.0);

	Mvec<double> centroid = (pt1 + pt2 + pt3) / 3;
	Mvec<double> circum = -circle2 / (NI < circle2);

	std::cout << "pt1 : " << pt1 << std::endl;
	std::cout << "circle1 : " << circle1 << std::endl;
	std::cout << "circle2 : " << circle2 << std::endl;
	std::cout << "circle3 : " << circle3 << std::endl;
	std::cout << "circle3.norm() : " << circle3.norm() << std::endl;
	std::cout << "centroid : " << centroid << std::endl;
	std::cout << "circum : " << circum << std::endl;

	Mvec<double> pt4 = point(1.0, 2.0);
	Mvec<double> pt5 = projectPointOnCircle(pt4, circle1);
	std::cout << "pt4 : " << pt4 << std::endl;
	std::cout << "pt5 : " << pt5 << std::endl;

	Mvec<double> pt6 = l1 | circle3;
	std::cout << "pt6 : " << pt6 << std::endl;

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
						pt4 = point(mainLight.pos().x, mainLight.pos().y);
						l1 = line(0.0, mainLight.pos().y, 0.0);
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

			pt6 = l1 | circle1;
			circle1 = pt1 ^ pt2 ^ pt3;
			centroid = (pt1 + pt2 + pt3) / 3;
			pt5 = projectPointOnCircle(pt4, circle1);
			// circum = -circle / (NI < circle);
			circum = -circle2 / (NI < circle2);

			// Red Triangle
			glColor3f(1.f, 0.f, 0.f);
			glVertex2f(pt1[E1], pt1[E2]);
			glVertex2f(pt2[E1], pt2[E2]);
			glVertex2f(pt3[E1], pt3[E2]);

			// Centroid
			glColor3f(0.f, 0.f, 1.f);
			glVertex2f(centroid[E1], centroid[E2]);

			// Point on light
			glColor3f(1.f, 1.f, 0.f);
			glVertex2f(pt4[E1], pt4[E2]);
			// Light Center projected on circle
			glColor3f(0.f, 1.f, 0.f);
			glVertex2f(pt5[E1], pt5[E2]);
			glVertex2f(pt6[E1], pt6[E2]);
			glVertex2f(circum[E1], circum[E2]);
		glEnd();

		drawLandmark();

		// Update the display
		windowManager.swapBuffers();
	}


	// // sample instructions
	// std::cout << "metric : \n" << c2ga::metric << std::endl;
	//
	// // accessor
	// Mvec<double> mv1;
	// mv1[scalar] = 1.0;
	// mv1[E0] = 42.0;
	// std::cout << "mv1 : " << mv1 << std::endl;
	//
	// Mvec<double> mv2;
	// mv2[E0] = 1.0;
	// mv2[E1] = 2.0;
	// mv2 += I<double>() + 2*e01<double>();
	// std::cout << "mv2 : " << mv2 << std::endl << std::endl;
	//
	// // some products
	// std::cout << "outer product     : " << (mv1 ^ mv2) << std::endl;
	// std::cout << "inner product     : " << (mv1 | mv2) << std::endl;
	// std::cout << "geometric product : " << (mv1 * mv2) << std::endl;
	// std::cout << "left contraction  : " << (mv1 < mv2) << std::endl;
	// std::cout << "right contraction : " << (mv1 > mv2) << std::endl;
	// std::cout << std::endl;
	//
	// // some tools
	// std::cout << "grade : " << mv1.grade()  << std::endl;
	// std::cout << "norm  : " << mv1.norm()  << std::endl;
	// mv1.clear();
	// if (mv1.isEmpty()) std::cout << "mv1 is empty: ok" << std::endl;

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
