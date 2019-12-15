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
	// Axe des abscisses rouge
	glBegin(GL_LINES);
		glColor3ub(255, 0, 0);
		glVertex2f(-1, 0);
		glVertex2f( 1, 0);
	glEnd();
	// Axe des ordonnées vert
	glBegin(GL_LINES);
		glColor3ub(0, 255, 0);
		glVertex2f(0, -1);
		glVertex2f(0,  1);
	glEnd();
}

int main() {
	std::cout << "Lancement du programme..." << std::endl;

	// Initialize SDL and open a window
	glimac::SDLWindowManager windowManager(WIDTH, HEIGHT, "GA Raytracer");
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-WIDTH/2.f, WIDTH/2.f, -HEIGHT/2.f, HEIGHT/2.f);

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
						case SDLK_z:
							// camera.moveFront(zoom);
							break;
						case SDLK_s:
							// camera.moveFront(-zoom);
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
						if (e.motion.xrel != 0)
							// camera.rotateUp(e.motion.xrel * speed);
						if (e.motion.yrel != 0)
							// camera.rotateLeft(e.motion.yrel * speed);
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

		// Add shapes
		glm::vec2 lightPos(0.f, 0.f);

		// Compute canvas
		glBegin(GL_POINTS);
		for (int i = -WIDTH/2.f + padding; i < WIDTH/2.f - padding; i++) {
			for (int j = -HEIGHT/2.f + padding; j < -HEIGHT/2.f - padding; j++) {
				float distance = sqrt(i*i + j*j);
				if (distance < 20.f) {
					glColor3f(1, 0, 0);
				} else {
					glColor3f(i / (WIDTH * 1.f), j / (HEIGHT * 1.f), 1.f);
				}

				// Get the pixel position
				pixelPos = glm::vec2(
					// i / (WIDTH * .5f) - 1.f,
					// j / (HEIGHT * .5f) - 1.f
					i,
					j
				);

				// Draw the pixel
				glVertex2f(pixelPos.x, pixelPos.y);
			}
		}
		glEnd();

		drawLandmark();

		// glBegin(GL_POINTS);
    //     glColor3f(1, 0, 0);
		// 		// glPointSize(10.0f); // wat
    //     glVertex2f(x, y);
    // glEnd();

		// time += 0.01f;

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
	// if(mv1.isEmpty()) std::cout << "mv1 is empty: ok" << std::endl;

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
