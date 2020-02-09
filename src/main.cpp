// C2GA
#include <c2ga/Mvec.hpp>

// C++ / OpenGL3
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <random>

// glimac
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/glm.hpp>

// gar (Geaometric Algebra Raytracer)
#include <gar/utils.hpp>
#include <gar/c2gaTools.hpp>
#include <gar/drawing.hpp>
#include <gar/Light.hpp>

using namespace c2ga;
using namespace gar;
using namespace glimac;

static const int WIDTH = 512;
static const int HEIGHT = 512;

class Vertex2DUV {
	public:
		Vertex2DUV();
		Vertex2DUV(const glm::vec2 &pos, const glm::vec2 &tex);
		glm::vec2 position;
		glm::vec2 texture;
};

Vertex2DUV::Vertex2DUV() {
	position = glm::vec2(0.f, 0.f);
	texture = glm::vec2(0.f, 0.f);
}

Vertex2DUV::Vertex2DUV(const glm::vec2 &pos, const glm::vec2 &tex) {
	position = pos;
	texture = tex;
}

glm::mat3 translate(float tx, float ty) {
	return glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(tx, ty, 1));
}

glm::mat3 scale(float sx, float sy) {
	return glm::mat3(glm::vec3(sx, 0, 0), glm::vec3(0, sy, 0), glm::vec3(0, 0, 1));
}

glm::mat3 rotate(float a) {
	a = glm::radians(a);
	return glm::mat3(glm::vec3(cos(a), sin(a), 0), glm::vec3(-sin(a), cos(a), 0), glm::vec3(0, 0, 1));
}

void resetCanvas(std::vector<glm::vec4> &pixelsColors, int &offsetStart, int& offsetEnd, const int &nbPixelsToDraw, bool &drawn) {
	std::fill(pixelsColors.begin(), pixelsColors.end(), glm::vec4(0., 0., 0., 1.));
	offsetStart = 0;
	offsetEnd = nbPixelsToDraw;
	drawn = false;
}

int main(int argc, char** argv) {
	std::cout << "Lancement du programme..." << std::endl;

	// Initialize SDL and open a window
	glimac::SDLWindowManager windowManager(WIDTH, HEIGHT, "GA Raytracer");
	// glViewport(0, 0, WIDTH, HEIGHT);
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();
	// gluOrtho2D(-WIDTH / 2.f, WIDTH / 2.f, -HEIGHT / 2.f, HEIGHT / 2.f);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_LINE_SMOOTH);

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if (GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	FilePath applicationPath(argv[0]);
	Program program = loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
																applicationPath.dirPath() + "shaders/tex2D.fs.glsl");

	program.use();
	GLint matrixLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");
	GLint colorLocation = glGetUniformLocation(program.getGLId(), "uColor");
	GLint textureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

	float time = 0.f;
	glm::mat3 transformMatrix = rotate(time);
	glm::vec3 color = glm::vec3(0.f);

	// Textures
	std::unique_ptr<Image> image = loadImage("/home/torresf/Documents/ga-raytracer/assets/triforce.png");

	if (image == NULL)
		std::cerr << "Erreur au chargement de l'image" << std::endl;

	std::vector<glm::vec4> pixelsColors(WIDTH * HEIGHT);
	std::vector<glm::ivec2> pixelsPositions(WIDTH * HEIGHT);

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			pixelsColors[(i * WIDTH) + j] = glm::vec4(0., 0., 0., 0.); // RGBA
			pixelsPositions[(i * WIDTH) + j] = glm::ivec2(i, j); // x, y
		}
	}

	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(pixelsPositions), std::end(pixelsPositions), rng);

	// std::cout << "myvector contains:";
	// for (int i = 0; i < pixelsPositions.size(); i++)
	// 	std::cout << ' ' << pixelsPositions.at(i) << std::endl;
	// std::cout << '\n';

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		WIDTH,
		WIDTH,
		0,
		GL_RGBA,
		GL_FLOAT,
		pixelsColors.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Création du VBO
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Binding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Envoie des données de vertex
	Vertex2DUV vertices[] = {
		Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)),
		Vertex2DUV(glm::vec2( 1, -1), glm::vec2(1, 1)),
		Vertex2DUV(glm::vec2( 1,  1), glm::vec2(1, 0)),
		Vertex2DUV(glm::vec2( -1,  1), glm::vec2(0, 0))
	};
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);

	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);
	// Activation de l'attribut de sommet 0 (la position)
	const GLuint VERTEX_ATTR_POSITION = 0;
	const GLuint VERTEX_ATTR_TEXTURE = 1;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

	// Spécification de l'attribut de sommet et de texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, position));
	glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, texture));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Débinding du VAO
	glBindVertexArray(0);

	glm::vec2 pixelPos;
	int padding = 0.f;

	// Light Setup
	Light mainLight(256.f, glm::vec2(90.f, 30.f));
	float ambientIntensity = 0.2f;
	float inObstacleColor = 0.01f;

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

	int nbPixelsToDraw = WIDTH * HEIGHT * .1;
	int offsetStart = 0;
	int offsetEnd = nbPixelsToDraw;
	bool drawn = false;

	// Application loop:
	float last_time_disp = 0.f;
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
							mainLight.size() += 25.f;
							if (mainLight.size() > 500.f) {
								mainLight.size() = 500.f;
							}
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						case SDLK_KP_MINUS:
							mainLight.size() -= 25.f;
							if (mainLight.size() < 0.f) {
								mainLight.size() = 0.f;
							}
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
						mainLight.pos() += glm::vec2(e.motion.xrel, -e.motion.yrel);
						pt1 = point(mainLight.pos().x, mainLight.pos().y);
						// Reset pixels to black
						resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
						// std::shuffle(std::begin(pixelsPositions), std::end(pixelsPositions), rng);
						break;
					}
				default:
					break;
			}
		}

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/

		// Update pixels colors
		float intensity = 0.f;
		bool isIntersected = false;
		bool isInCircle = false;
		float distanceFromLight;

		// Compute pixels
		if (!drawn) {
			// Shuffle pixelsPositions
			if (offsetStart == 0)
				std::shuffle(std::begin(pixelsPositions), std::end(pixelsPositions), rng);

			if (offsetStart <= WIDTH * HEIGHT) {
				for (int i = offsetStart; i <= offsetEnd; i++) {
					// Compute pixel color
					auto coordX = pixelsPositions[i].x;
					auto coordY = pixelsPositions[i].y;
					auto idx = coordX * WIDTH + coordY;

					// Get the multivector (point) from X and Y coords of the pixel
					auto currentPixel = point((double) coordY - WIDTH*.5, - (double) coordX + HEIGHT*.5);

					// Get the distance between the pixel and the light
					distanceFromLight = distance(point(mainLight.pos()), currentPixel);
					if (distanceFromLight > mainLight.size()) {
						// The pixel is too far from the light source
						intensity = ambientIntensity; // We show the ambiant light
					} else {
						isIntersected = false;
						isInCircle = false;
						for (auto &obstacle : obstacles) {

							if (isPointInCircle(currentPixel, obstacle)) {
								isIntersected = true;
								isInCircle = true;
								break;
							}

							if (areIntersected(line(currentPixel, pt1), obstacle)) {
								if (distance(projectPointOnCircle(currentPixel, obstacle), pt1) <= distance(currentPixel, pt1)) {
									isIntersected = true;
									// break;
								}
							}
						}
						if (isIntersected) {
							if (isInCircle) {
								intensity = inObstacleColor;
							} else {
								intensity = ambientIntensity;
							}
						} else {
							intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), ambientIntensity, 1.f, 1.f);
						}
					}

					pixelsColors[idx] = glm::vec4(intensity, intensity, intensity, 1.); // RGBA

				}
				offsetStart = offsetEnd + 1;
				offsetEnd = offsetStart + nbPixelsToDraw;
			} else {
				drawn = true;
			}
			if (offsetEnd > WIDTH * HEIGHT) {
				offsetEnd = WIDTH * HEIGHT;
			}
		}

		// #pragma omp parallel for
		// for (int i = 0; i < WIDTH; i++) {
			// #pragma omp parallel for
			// for (int j = 0; j < HEIGHT; j++) {
				// if (i == 0 && j == 0) {
					// auto currentPixel = point((double) j - WIDTH*.5, - (double) i + HEIGHT*.5);
				// }

				// distanceFromLight = distance(point(mainLight.pos()), currentPixel);
				// if (distanceFromLight > mainLight.size()) {
				// 	// The pixel is too far from the light source
				// 	intensity = ambientIntensity;
				// } else {
				// 	// float intensity = lerp(ambientIntensity, 1., 1. - (distance / lightSize));
				// 	isIntersected = false;
				// 	for (auto &obstacle : obstacles) {
				//
				// 		if (isPointInCircle(currentPixel, obstacle)) {
				// 			isIntersected = true;
				// 			break;
				// 		}
				//
				// 		if (areIntersected(line(currentPixel, pt1), obstacle)) {
				// 			if (distance(projectPointOnCircle(currentPixel, obstacle), pt1) <= distance(currentPixel, pt1)) {
				// 				isIntersected = true;
				// 				break;
				// 			}
				// 		}
				// 	}
				// 	if (isIntersected) {
				// 		intensity = ambientIntensity;
				// 	} else {
				// 		intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), ambientIntensity, 1.f, 1.f);
				// 	}
				// 	// glColor3f(intensity, intensity, intensity);
				// }

				// pixels[(i * WIDTH) + j] = glm::vec4((double) i / WIDTH * cos(time/5), 0., sin(time/10), 1.); // RGBA
				// pixels[(i * WIDTH) + j] = glm::vec4(1., 1., 0., 1.); // RGBA
				// pixels[(i * WIDTH) + j] = glm::vec4(sin(time), intensity, intensity, 1.); // RGBA
				// pixels[(i * WIDTH) + j] = glm::vec4(intensity, intensity, intensity, 1.); // RGBA
			// }
		// }

		// Update texture
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D,
			0,
			GL_RGBA,
			WIDTH,
			WIDTH,
			0,
			GL_RGBA,
			GL_FLOAT,
			pixelsColors.data());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glUniform1i(textureLocation, 0);

		// Clear canvas
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw Quad
		glBindVertexArray(vao);

		// transformMatrix = rotate(time*50.f) * translate(0.5, 0.5) * scale(0.25, 0.25) * rotate(-time);
		transformMatrix = glm::mat3();
		color = glm::vec3(1.f, cos(time * .5f), sin(time *.5f));
		glUniformMatrix3fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));
		glDrawArrays(GL_QUADS, 0, 4);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		time += 0.01;

		// Set point size (1 = 1px)
		// glPointSize(5.f);
		// drawLandmark(WIDTH, HEIGHT);

		// circle1 = pt1 ^ pt2 ^ pt3;
		// circum = -circle1 / (ei<double>() < circle1);
		// circlePos.x = circum[E1];
		// circlePos.y = circum[E2];
		// circleRadius = distance(circum, pt1);
		// circle2Pos.x = circum2[E1];
		// circle2Pos.y = circum2[E2];
		// pp1 = circle1 | circle2;
		// pp2 = pt1 ^ pt2;
		// pp2_1 = pp2 / (- pp2 | ei<double>());
		// pp2_1 = -pp2_1;
		// pp4 = getIntersection(circle1, circle2);
		// pp4_line = pp4 ^ ei<double>();
		//
		// l0 = pt1 ^ pt2 ^ ei<double>();
		// intersection2 = e0<double>() | getIntersection(l1, l0);
		// intersection2 = normalize(intersection2);
		// intersection3 = e0<double>() | getIntersection(l2, l0);
		// intersection3 = normalize(intersection3);
		//
		// pt1_on_l1 = projectPointOnLine(pt1, l1);
		// pt1_on_l2 = projectPointOnLine(pt1, l2);
		//
		// pt5 = projectPointOnCircle(pt1, circle2);

		// Compute canvas
#if 0
		glBegin(GL_POINTS);
#pragma omp parallel for
			for (int i = -WIDTH/2 + padding; i < WIDTH/2 - padding; i++) {
#pragma omp parallel for
				for (int j = -HEIGHT/2 + padding; j < HEIGHT/2 - padding; j++) {
					{
						auto currentPixel = point((double) i, (double) j);

						// float distanceFromLight = sqrt((mainLight.pos().x - i) * (mainLight.pos().x - i) + (mainLight.pos().y - j) * (mainLight.pos().y - j));
						float distanceFromLight = distance(point(mainLight.pos()), currentPixel);
						if (distanceFromLight > mainLight.size()) {
							// The pixel is too far from the light source
							glColor3f(ambientIntensity, ambientIntensity, ambientIntensity);
						} else {
							// float intensity = lerp(ambientIntensity, 1., 1. - (distance / lightSize));
							bool isIntersected = false;
							for (auto &obstacle : obstacles) {

								if (isPointInCircle(currentPixel, obstacle)) {
									isIntersected = true;
									break;
								}

								if (areIntersected(line(currentPixel, pt1), obstacle)) {
									if (distance(projectPointOnCircle(currentPixel, obstacle), pt1) <= distance(currentPixel, pt1)) {
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
			}
#endif
#if 0
			// RED
			glColor3f(1.f, 0.f, 0.f);
			// drawPoint(pt2);
			// drawPoint(pt3);
			drawPoint(intersection1);
			drawPoint(pt1_on_l1);
			drawPoint(pt1_on_l2);
			drawPoint(projectPointOnCircle(pt1, circle3));

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

			if (isPointInCircle(pt1, circle2)) {
				glColor3f(1.f, 0.f, 0.f);
			} else {
				glColor3f(1.f, 1.f, 0.f);
			}
			drawPoint(pt1);

			if ((pp4*pp4) >= 0) {
				glColor3f(1.f, 0.f, 0.f);
			} else {
				glColor3f(1.f, 1.f, 1.f);
			}
			drawPointPair(pp4);
			drawPointPair(pp3);

			glColor3f(1.f, 0.f, 1.f);
			drawPoint(pt5);
			drawPoint(l1 * pt1 / l1);

		glEnd(); // End draw GL_POINTS

		glColor3f(0.f, 0.f, 1.f);
		drawLine(a, b);
		glColor3f(0.f, 1.f, 0.f);
		drawLine(c, d);
		drawCircle(circum2, circle2Radius);
		drawLine(pp4);

		glColor3f(1.f, 1.f, 0.f);
		// drawCircle(circum, circleRadius);
		drawCircle(circum3, circle3Radius);

#endif

		// Update the display
		windowManager.swapBuffers();

		// FPS count
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end-start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		// std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
		// std::cout << "time: " << time << std::endl;
		// std::cout << "fmod(time, 10.f): " << fmod(time, 10.f) << std::endl;
		if (last_time_disp > 5.f) {
			std::cout << 1.0 / elapsed_seconds.count() << " FPS" << std::endl;
			last_time_disp = 0.f;
		}
		last_time_disp += 0.01f;
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
