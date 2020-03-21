/*
 * Author : Florian TORRES
 * Date : March 2020
 */

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
	GLint intensityLocation = glGetUniformLocation(program.getGLId(), "uIntensity");
	GLint textureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

	float time = 0.f;
	glm::mat3 transformMatrix = rotate(time);
	glm::vec3 color = glm::vec3(1.f);
	glm::vec3 lightIntensity = glm::vec3(1.f, .9f, .8f);
	float lightIntensityMult = 1.5f;

	// Texture
	std::vector<glm::vec4> pixelsColors(WIDTH * HEIGHT);
	std::vector<glm::ivec2> pixelsPositions(WIDTH * HEIGHT);

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			pixelsColors[(i * WIDTH) + j] = glm::vec4(0., 0., 0., 0.); // RGBA
			pixelsPositions[(i * WIDTH) + j] = glm::ivec2(i, j); // x, y
		}
	}

	// Randomize pixel positions
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(pixelsPositions), std::end(pixelsPositions), rng);

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

	// VBO creation and binding
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Sending vertices data
	Vertex2DUV vertices[] = {
		Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 1)),
		Vertex2DUV(glm::vec2( 1, -1), glm::vec2(1, 1)),
		Vertex2DUV(glm::vec2( 1,  1), glm::vec2(1, 0)),
		Vertex2DUV(glm::vec2( -1,  1), glm::vec2(0, 0))
	};
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);

	// VBO Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// VAO creation and binding
	GLuint vao;
	glGenVertexArrays(1, &vao);
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

	// VAO unbind
	glBindVertexArray(0);

	// Light Setup
	Light mainLight(350.f, 512.f, glm::vec2(90.f, 30.f));
	float ambientIntensity = 0.2f;
	float inObstacleColor = 0.01f;

	// Add circle
	glm::vec2 circlePos(-50.f, 80.f);
	float circleRadius = 40.f;
	glm::vec2 circle2Pos(0.f, 0.f);
	float circle2Radius = 60.f;
	float circle3Radius = 40.f;

	Mvec<double> lightPosition = point(90.0, 30.0);
	Mvec<double> pt1 = point(-80.0, 30.0);
	Mvec<double> pt2 = point(30.0, 50.0);
	Mvec<double> pt3 = point(50.0, 20.0);

	Mvec<double> l0 = lightPosition ^ pt2 ^ ei<double>();
	// Mvec<double> circle1 = pt1 ^ pt2 ^ pt3;
	Mvec<double> circle1 = circle(-80, -120, 20);
	Mvec<double> circle2 = circle(-80, 50, 60);
	Mvec<double> circle3 = circle(-70, 120, 40);
	Mvec<double> circle4 = circle(120, -100, 80);
	Mvec<double> circum = getCenterOfCircle(circle1);
	Mvec<double> circum2 = getCenterOfCircle(circle2);
	Mvec<double> circum3 = getCenterOfCircle(circle3);

	Mvec<double> pt4 = point(0.0, 0.0);
	Mvec<double> pt5 = projectPointOnCircle(pt4, circle1);

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

	Mvec<double> pp2 = lightPosition ^ pt2;
	std::cout << "pp2 : " << pp2 << std::endl;
	Mvec<double> pp2_1; // First point of pp2 pair point
	Mvec<double> pp2_2; // Second point of pp2 pair point

	Mvec<double> pp3 = getIntersection(circle2, circle3);
	std::cout << "pp3 : " << pp3 << std::endl;

	Mvec<double> pp4 = getIntersection(circle1, circle2);
	std::cout << "pp4 : " << pp4 << std::endl;
	Mvec<double> pp4_line;

	Mvec<double> lightPosition_on_l1;
	Mvec<double> lightPosition_on_l2;

	std::vector<Mvec<double>> obstacles;
	obstacles.push_back(circle1);
	obstacles.push_back(circle2);
	obstacles.push_back(circle3);
	obstacles.push_back(circle4);

	auto lastTime = std::chrono::system_clock::now();
	int nbFrames = 0;

	// Iterative drawing
	int nbPixelsTotal = WIDTH * HEIGHT;
	int nbPixelsToDraw = nbPixelsTotal * .05; // We draw only 5% of the image at each draw loop until the all image is processed
	int offsetStart = 0;
	int offsetEnd = nbPixelsToDraw;
	bool drawn = false;

	// Init pixel informations
	float intensity = 0.f;
	bool isIntersected = false;
	bool isInCircle = false;
	float distanceFromLight;
	int showShadows = 2; // 0: No shadows, 1: Basic shadows, 2: Advanced shadows

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
							mainLight.size() += 25.f;
							mainLight.size() = std::min(mainLight.size(), mainLight.maxSize());
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						case SDLK_KP_MINUS:
							mainLight.size() -= 25.f;
							mainLight.size() = std::max(mainLight.size(), 0.f);
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						case SDLK_UP:
							lightIntensityMult += .5f;
							lightIntensityMult = std::min(lightIntensityMult, 4.f);
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						case SDLK_DOWN:
							lightIntensityMult -= .5f;
							lightIntensityMult = std::max(lightIntensityMult, 0.f);
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						case SDLK_s:
							showShadows = (showShadows + 1) % 3;
							if (showShadows == 0)
								std::cout << "No shadows" << std::endl;
							if (showShadows == 1)
								std::cout << "Basic shadows" << std::endl;
							if (showShadows == 2)
								std::cout << "Advanced shadows" << std::endl;
							resetCanvas(pixelsColors, offsetStart, offsetEnd, nbPixelsToDraw, drawn);
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
						mainLight.pos() += glm::vec2(e.motion.xrel, -e.motion.yrel);
						lightPosition = point(mainLight.pos().x, mainLight.pos().y);
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Init pixel informations
		intensity = 0.f;
		isIntersected = false;
		isInCircle = false;
		distanceFromLight;

#if 1
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
					auto closeToCircle = false;
					auto distanceFromBackPoint = 0.f;
					auto lessDistanceFromBackPoint = 0.f;

					// Get the multivector (point) from X and Y coords of the pixel
					auto currentPixel = point((double)coordY - WIDTH * .5, -(double)coordX + HEIGHT * .5);

					// Get the distance between the pixel and the light source
					distanceFromLight = distance(point(mainLight.pos()), currentPixel);
					if (distanceFromLight > mainLight.size()) {
						// The pixel is too far from the light source
						intensity = ambientIntensity; // We show the ambiant light
					} else {
						isIntersected = false;
						isInCircle = false;
						for (auto &obstacle : obstacles) {

							if (isPointInCircle(currentPixel, obstacle))
							{
								isIntersected = true;
								isInCircle = true;
								break;
							}

							if (showShadows > 0)
							{
								if (areIntersected(line(currentPixel, lightPosition), obstacle))
								{
									auto interBetweenLightAndObstacle = getIntersection(line(currentPixel, lightPosition), obstacle);
									auto frontPoint = getFirstPointFromPointPair(interBetweenLightAndObstacle);
									auto backPoint = getSecondPointFromPointPair(interBetweenLightAndObstacle);

									// BASIC SHADOWS
									// Detect if the pixel is in shadow of an obstacle
									if (distance(currentPixel, lightPosition) >= distance(currentPixel, frontPoint))
									{
										if (distance(projectPointOnCircle(currentPixel, obstacle), lightPosition) <= distance(currentPixel, lightPosition))
										{
											isIntersected = true;
										}
									}


									// // ADVANCED SHADOWS
									if (showShadows == 2) {
										// Detect if the pixel is in the shadow near the obstacle
										distanceFromBackPoint = distance(backPoint, currentPixel);
										if (distanceFromBackPoint < 25.f)
										{
											closeToCircle = true;
											lessDistanceFromBackPoint = distanceFromBackPoint;
										}
									}
								}
							}
						}

						intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), ambientIntensity, 1.f, 1.5f);

						if (isIntersected) {
							if (isInCircle) {
								// The pixel is in a circle
								intensity = easeIn(1.f - (distanceFromLight / mainLight.size()), inObstacleColor, ambientIntensity, 1.f);
								intensity = lerp(ambientIntensity, intensity, 1.f - (distanceFromLight / mainLight.size()));
							} else {
								// The pixel is not is behind a circle
								intensity = ambientIntensity;
								if (closeToCircle) {
									intensity = lerp(ambientIntensity * .7f, ambientIntensity, lessDistanceFromBackPoint / 25.f);
								}
							}
						} else {
							if (closeToCircle) {
								// intensity = lerp(ambientIntensity, intensity, 1.f - (distanceFromLight / mainLight.size()));
								intensity = easeIn(1.f - lessDistanceFromBackPoint / 30.f, intensity, 1.f, 1.f);
							}
						}
					}
					pixelsColors[idx] = glm::vec4(intensity, intensity, intensity, 1.); // RGBA
				}

				offsetStart = offsetEnd + 1;
				offsetEnd = offsetStart + nbPixelsToDraw;
				if (offsetEnd > nbPixelsTotal) {
					offsetEnd = nbPixelsTotal;
				}
			} else {
				drawn = true;
			}
		}

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

		transformMatrix = glm::mat3();
		// color = glm::vec3(1.f, cos(time * .5f), sin(time *.5f));
		glUniformMatrix3fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));
		glUniform3fv(intensityLocation, 1, glm::value_ptr(lightIntensity * lightIntensityMult));
		glDrawArrays(GL_QUADS, 0, 4);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
#endif
		time += 0.01;
#if 0

		// Set point size (1 = 1px)
		glPointSize(5.f);
		drawLandmark(WIDTH, HEIGHT);

		circle1 = lightPosition ^ pt2 ^ pt3;
		circum = -circle1 / (ei<double>() < circle1);
		circlePos.x = circum[E1];
		circlePos.y = circum[E2];
		circleRadius = distance(circum, lightPosition);
		circle2Pos.x = circum2[E1];
		circle2Pos.y = circum2[E2];
		pp1 = circle1 | circle2;
		pp2 = lightPosition ^ pt2;
		pp2_1 = pp2 / (- pp2 | ei<double>());
		pp2_1 = -pp2_1;
		pp4 = getIntersection(circle1, circle2);
		pp4_line = pp4 ^ ei<double>();
		
		l0 = lightPosition ^ pt2 ^ ei<double>();
		intersection2 = e0<double>() | getIntersection(l1, l0);
		intersection2 = normalize(intersection2);
		intersection3 = e0<double>() | getIntersection(l2, l0);
		intersection3 = normalize(intersection3);
		
		lightPosition_on_l1 = projectPointOnLine(lightPosition, l1);
		lightPosition_on_l2 = projectPointOnLine(lightPosition, l2);
		
		pt5 = projectPointOnCircle(lightPosition, circle2);

		glBegin(GL_POINTS);
			// RED
			glColor3f(1.f, 0.f, 0.f);
			drawPoint(pt2);
			drawPoint(pt3);
			drawPoint(intersection1);
			drawPoint(lightPosition_on_l1);
			drawPoint(lightPosition_on_l2);
			drawPoint(projectPointOnCircle(lightPosition, circle3));

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

			if (isPointInCircle(lightPosition, circle2)) {
				glColor3f(1.f, 0.f, 0.f);
			} else {
				glColor3f(1.f, 1.f, 0.f);
			}
			drawPoint(lightPosition);

			if ((pp4*pp4) >= 0) {
				glColor3f(1.f, 0.f, 0.f);
			} else {
				glColor3f(1.f, 1.f, 1.f);
			}
			drawPointPair(pp4);
			drawPointPair(pp3);

			glColor3f(1.f, 0.f, 1.f);
			drawPoint(pt5);
			drawPoint(l1 * lightPosition / l1);

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
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		if (fmod(time, 10.f) < .1f)
		{
			std::cout << "time: " << time << std::endl;
			std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
			std::cout << 1.0 / elapsed_seconds.count() << " FPS" << std::endl;
		}
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);

	std::cout << "Fin du programme." << std::endl;
	return EXIT_SUCCESS;
}
