// C2GA
#include <c2ga/Mvec.hpp>

// OpenGL3
#include <GL/glew.h>
#include <iostream>
#include <vector>

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


	Mvec<double> n0 = 0.5 * (ei<double>() - e0<double>());
	Mvec<double> ni = e0<double>() + ei<double>();

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

	Mvec<double> pt1;
	pt1 = n0 + x1*e1<double>() - y1*e2<double>() + 0.5*(x1*x1+y1*y1)*ni;

	// Mvec<double> pt2;
	// pt2[scalar] = 1.0;
	// pt2[E1] = 20.0;
	// pt2[E2] = 50.0;
	// pt2[Ei] = 0.5*(pt2[E1]*pt2[E1]+pt2[E2]*pt2[E2]);

	Mvec<double> pt2;
	pt2 = n0 + x2*e1<double>() - y2*e2<double>() + 0.5*(x2*x2+y2*y2)*ni;

	Mvec<double> pt3;
	pt3 = n0 + x3*e1<double>() - y3*e2<double>() + 0.5*(x3*x3+y3*y3)*ni;

	// Mvec<double> pt3;
	// pt3[scalar] = 1.0;
	// pt3[E1] = 50.0;
	// pt3[E2] = 20.0;
	// pt3[Ei] = 0.5*(pt3[E1]*pt3[E1]+pt3[E2]*pt3[E2]);

	Mvec<double> circle = pt1 ^ pt2 ^ pt3;
	Mvec<double> centroid = (pt1 + pt2 + pt3) / 3;
	Mvec<double> circum = -circle / (ni < circle);
	std::cout << "pt1 : " << pt1 << std::endl;
	std::cout << "circle : " << circle << std::endl;
	std::cout << "centroid : " << centroid << std::endl;
	std::cout << "circum : " << circum << std::endl;

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
						pt1[E1] = mainLight.pos().x;
						pt1[E2] = mainLight.pos().y;
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

			circle = pt1 ^ pt2 ^ pt3;
			centroid = (pt1 + pt2 + pt3) / 3;
			circum = -circle / (ni < circle);

			glColor3f(1.f, 0.f, 0.f);
			// glPointSize(10);
			glVertex2f(pt1[E1], pt1[E2]);
			glVertex2f(pt2[E1], pt2[E2]);
			glVertex2f(pt3[E1], pt3[E2]);
			glColor3f(0.f, 0.f, 1.f);
			glVertex2f(centroid[E1], centroid[E2]);
			glColor3f(0.f, 1.f, 0.f);
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
