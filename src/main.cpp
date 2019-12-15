// C2GA
#include <c2ga/Mvec.hpp>

// OpenGL3
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

using namespace c2ga;

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
	int padding = 10.f;

	// Light Setup
	glm::vec2 lightPos(50.f, 100.f);
	float lightSize = 200.f;
	float ambientIntensity = 0.05f;

	// Add shape
	glm::vec2 circlePos(-50.f, 80.f);
	float circleRadius = 40.f;

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
							lightSize += 10.f;
							if (lightSize > 500.f) {
									lightSize = 500.f;
							}
							break;
						case SDLK_KP_MINUS:
							lightSize -= 10.f;
							if (lightSize < 0.f) {
								lightSize = 0.f;
							}
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
						lightPos += glm::vec2(e.motion.xrel, -e.motion.yrel);
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
		glPointSize(1.f);

		// Compute canvas
		glBegin(GL_POINTS);
			for (int i = -WIDTH/2 + padding; i < WIDTH/2 - padding; i++) {
				for (int j = -HEIGHT/2 + padding; j < HEIGHT/2 - padding; j++) {

					float distanceFromLight = sqrt((lightPos.x - i) * (lightPos.x - i) + (lightPos.y - j) * (lightPos.y - j));
					if (distanceFromLight > lightSize) {
						// The pixel is too far from the light source
						glColor3f(ambientIntensity, ambientIntensity, ambientIntensity);
					} else {
						// float intensity = lerp(ambientIntensity, 1., 1. - (distance / lightSize));
						float intensity = easeIn(1.f - (distanceFromLight / lightSize), ambientIntensity, 1.f, 1.f);
						glColor3f(intensity, intensity, intensity);
					}

					float distanceFromCircle = sqrt((circlePos.x - i) * (circlePos.x - i) + (circlePos.y - j) * (circlePos.y - j));
					if (distanceFromCircle < circleRadius && distanceFromCircle > circleRadius - 2.f) {
						glColor3f(1., ambientIntensity, ambientIntensity);
					}

					glVertex2f(i, j);
				}
			}
		glEnd();

		drawLandmark();

		// Update the display
		windowManager.swapBuffers();
	}

	// sample instructions
	std::cout << "metric : \n" << c2ga::metric << std::endl;

	// accessor
	Mvec<double> mv1;
	mv1[scalar] = 1.0;
	mv1[E0] = 42.0;
	std::cout << "mv1 : " << mv1 << std::endl;

	Mvec<double> mv2;
	mv2[E0] = 1.0;
	mv2[E1] = 2.0;
	mv2 += I<double>() + 2*e01<double>();
	std::cout << "mv2 : " << mv2 << std::endl << std::endl;

	// some products
	std::cout << "outer product     : " << (mv1 ^ mv2) << std::endl;
	std::cout << "inner product     : " << (mv1 | mv2) << std::endl;
	std::cout << "geometric product : " << (mv1 * mv2) << std::endl;
	std::cout << "left contraction  : " << (mv1 < mv2) << std::endl;
	std::cout << "right contraction : " << (mv1 > mv2) << std::endl;
	std::cout << std::endl;

	// some tools
	std::cout << "grade : " << mv1.grade()  << std::endl;
	std::cout << "norm  : " << mv1.norm()  << std::endl;
	mv1.clear();
	if(mv1.isEmpty()) std::cout << "mv1 is empty: ok" << std::endl;

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
