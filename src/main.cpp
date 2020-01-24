// C2GA
#include <c2ga/Mvec.hpp>

// C++ / OpenGL3
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <ctime>

// glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

// gar (Geaometric Algebra Raytracer)
#include <gar/utils.hpp>
#include <gar/c2gaTools.hpp>
#include <gar/drawing.hpp>
#include <gar/Light.hpp>

using namespace c2ga;
using namespace gar;

static const int WIDTH = 500;
static const int HEIGHT = 500;

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
	Light mainLight(150.f, glm::vec2(90.f, 30.f));
	float ambientIntensity = 0.05f;

	// Add circle
	glm::vec2 circlePos(-50.f, 80.f);
	float circleRadius = 40.f;
	glm::vec2 circle2Pos(0.f, 0.f);
	float circle2Radius = 60.f;
	float circle3Radius = 40.f;

	Mvec<double> pt1 = point(90.0, 30.0);
	Mvec<double> pt2 = point(30.0, 50.0);
	Mvec<double> pt3 = point(50.0, 20.0);

	Mvec<double> l0 = pt1 ^ pt2 ^ ei<double>();
	Mvec<double> circle1 = pt1 ^ pt2 ^ pt3;
	Mvec<double> circle2 = circle(-80, 50, 60);
	Mvec<double> circle3 = circle(-70, 120, 40);
	Mvec<double> circum = getCenterOfCircle(circle1);
	Mvec<double> circum2 = getCenterOfCircle(circle2);
	Mvec<double> circum3 = getCenterOfCircle(circle3);

	// Normalize point
	// point /= - point | ei<double>(); // = composante en E0

	std::cout << "pt1 : " << pt1 << std::endl;
	std::cout << "l0 : " << l0 << std::endl;
	std::cout << "l0.grade() : " << l0.grade() << std::endl;
	std::cout << "circle1 : " << circle1 << std::endl;
	std::cout << "circle2 : " << circle2 << std::endl;
	std::cout << "circle3 : " << circle3 << std::endl;

	Mvec<double> pt4 = point(0.0, 0.0);
	Mvec<double> pt5 = projectPointOnCircle(pt4, circle1);
	std::cout << "pt4 : " << pt4 << std::endl;
	std::cout << "pt5 : " << pt5 << std::endl;
	std::cout << "pt4.grade() : " << pt4.grade() << std::endl;
	std::cout << "pt5.grade() : " << pt5.grade() << std::endl;

	Mvec<double> a = point(-120, -150);
	Mvec<double> b = point(-120, -50);
	Mvec<double> c = point(-200, -60);
	Mvec<double> d = point(-100, -120);

	Mvec<double> l1 = line(a, b);
	Mvec<double> l2 = line(c, d);

	Mvec<double> intersection1 = e0<double>() | getIntersection(l1, l2);
	intersection1 = normalize(intersection1);

	Mvec<double> intersection2 = e0<double>() | getIntersection(l1, l0);
	intersection2 = normalize(intersection2);

	Mvec<double> intersection3 = e0<double>() | getIntersection(l2, l0);
	intersection3 = normalize(intersection3);

	Mvec<double> pp1 = circle1 / circle2;
	std::cout << "pp1 : " << pp1 << std::endl;

	Mvec<double> pp2 = pt1 ^ pt2;
	std::cout << "pp2 : " << pp2 << std::endl;
	Mvec<double> pp2_1; // First point of pp2 pair point
	Mvec<double> pp2_2; // Second point of pp2 pair point

	Mvec<double> pp3 = getIntersection(circle2, circle3);
	std::cout << "pp3 : " << pp3 << std::endl;

	Mvec<double> pp4 = getIntersection(circle1, circle2);
	std::cout << "pp4 : " << pp4 << std::endl;
	Mvec<double> pp4_line;

	Mvec<double> pt1_on_l1;
	Mvec<double> pt1_on_l2;

	std::vector<Mvec<double>> obstacles;
	obstacles.push_back(circle2);
	obstacles.push_back(circle3);

	auto lastTime = std::chrono::system_clock::now();
	int nbFrames = 0;

	// Application loop:
	bool done = false;
	while (!done) {

		auto start = std::chrono::system_clock::now();

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
						pt1 = point(mainLight.pos().x, mainLight.pos().y);
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
		drawLandmark(WIDTH, HEIGHT);

		circle1 = pt1 ^ pt2 ^ pt3;
		circum = -circle1 / (ei<double>() < circle1);
		circlePos.x = circum[E1];
		circlePos.y = circum[E2];
		circleRadius = distance(circum, pt1);
		circle2Pos.x = circum2[E1];
		circle2Pos.y = circum2[E2];
		pp1 = circle1 | circle2;
		pp2 = pt1 ^ pt2;
		pp2_1 = pp2 / (- pp2 | ei<double>());
		pp2_1 = -pp2_1;
		pp4 = getIntersection(circle1, circle2);
		pp4_line = pp4 ^ ei<double>();

		l0 = pt1 ^ pt2 ^ ei<double>();
		intersection2 = e0<double>() | getIntersection(l1, l0);
		intersection2 = normalize(intersection2);
		intersection3 = e0<double>() | getIntersection(l2, l0);
		intersection3 = normalize(intersection3);

		pt1_on_l1 = projectPointOnLine(pt1, l1);
		pt1_on_l2 = projectPointOnLine(pt1, l2);

		pt5 = projectPointOnCircle(pt1, circle2);

		// Compute canvas
		glBegin(GL_POINTS);
#if 0
			for (int i = -WIDTH/2 + padding; i < WIDTH/2 - padding; i++) {
				for (int j = -HEIGHT/2 + padding; j < HEIGHT/2 - padding; j++) {

					float distanceFromLight = sqrt((mainLight.pos().x - i) * (mainLight.pos().x - i) + (mainLight.pos().y - j) * (mainLight.pos().y - j));
					if (distanceFromLight > mainLight.size()) {
						// The pixel is too far from the light source
						glColor3f(ambientIntensity, ambientIntensity, ambientIntensity);
					} else {
						// float intensity = lerp(ambientIntensity, 1., 1. - (distance / lightSize));
						bool isIntersected = false;
						for (auto &obstacle : obstacles) {
							// If intersect between point(i,j) and obstacle, black, else compute intensity
							if (areIntersected(line(point((double)i, (double)j), pt1), obstacle)) {
								if (distance(projectPointOnCircle(point((double)i, (double)j), obstacle), pt1) <= distance(point((double)i, (double)j), pt1)) {
									isIntersected = true;
									break;
								}
							}
						}
						float intensity;
						if (isIntersected) {
							intensity = ambientIntensity;
						} else {
							intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), ambientIntensity, 1.f, 1.f);
						}
						glColor3f(intensity, intensity, intensity);
					}

					// float distanceFromCircle = sqrt((circlePos.x - i) * (circlePos.x - i) + (circlePos.y - j) * (circlePos.y - j));
					// if (distanceFromCircle < circleRadius && distanceFromCircle > circleRadius - 2.f) {
					// 	glColor3f(1., ambientIntensity, ambientIntensity);
					// }
					//
					// distanceFromCircle = sqrt((circle2Pos.x - i) * (circle2Pos.x - i) + (circle2Pos.y - j) * (circle2Pos.y - j));
					// if (distanceFromCircle < circle2Radius && distanceFromCircle > circle2Radius - 2.f) {
					// 	glColor3f(ambientIntensity, 1., ambientIntensity);
					// }

					glVertex2f(i, j);
				}
			}
#endif
			// RED
			glColor3f(1.f, 0.f, 0.f);
			drawPoint(pt1);
			// drawPoint(pt2);
			// drawPoint(pt3);
			drawPoint(intersection1);
			drawPoint(pt1_on_l1);
			drawPoint(pt1_on_l2);

			// BLUE
			glColor3f(0.f, 0.f, 1.f);
			drawPoint(a);
			drawPoint(b);

			// YELLOW
			// Point on light
			glColor3f(1.f, 1.f, 0.f);
			drawPoint(intersection2);
			drawPoint(intersection3);

			// GREEN
			glColor3f(0.f, 1.f, 0.f);
			// Light center projected on circle
			// drawPoint(circum);
			drawPoint(circum2);
			drawPoint(circum3);
			drawPoint(c);
			drawPoint(d);

			if ((pp4*pp4) >= 0) {
				glColor3f(1.f, 0.f, 0.f);
			} else {
				glColor3f(1.f, 1.f, 1.f);
			}
			drawPointPair(pp4);
			drawPointPair(pp3);

			glColor3f(1.f, 0.f, 1.f);
			drawPoint(pt5);

		glEnd();

		glColor3f(0.f, 0.f, 1.f);
		drawLine(a, b);
		glColor3f(0.f, 1.f, 0.f);
		drawLine(c, d);
		drawCircle(circum2, circle2Radius);
		drawLine(pp4);

		glColor3f(1.f, 1.f, 0.f);
		// drawCircle(circum, circleRadius);
		drawCircle(circum3, circle3Radius);

		// Update the display
		windowManager.swapBuffers();

		// FPS count
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		// std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
		// std::cout << 1.0 / elapsed_seconds.count() << " FPS" << std::endl;
	}

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
