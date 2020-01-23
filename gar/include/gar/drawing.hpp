#pragma once
#ifndef __DRAWING__HPP
#define __DRAWING__HPP

using namespace c2ga;

namespace gar {

void drawLandmark(const int width, const int height) {
	float padding = 10.f;
	// Axe des abscisses rouge
	glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		glVertex2f(-width / 2.f + padding, 0);
		glVertex2f( width / 2.f - padding, 0);
	glEnd();
	// Axe des ordonnées vert
	glBegin(GL_LINES);
		glColor3ub(255, 255, 255);
		glVertex2f(0, -height / 2.f + padding);
		glVertex2f(0,  height / 2.f - padding);
	glEnd();
}

template<typename T>
void drawPoint(const Mvec<T> &p) {
	glVertex2f(p[E1], p[E2]);
}

template<typename T>
void drawPointPair(const Mvec<T> &pp) {
	if (pp.norm()*pp.norm() > 0) {
		// 2 points
		Mvec<T> p1 = (pp + sqrt(pp*pp)) / (-ei<double>() | pp);
		Mvec<T> p2 = (pp - sqrt(pp*pp)) / (-ei<double>() | pp);
		drawPoint(p1);
		drawPoint(p2);
	}
}

template<typename T>
void drawLine(const Mvec<T> &p1, const Mvec<T> &p2) {
	glBegin(GL_LINES);
		glVertex2f(p1[E1], p1[E2]);
		glVertex2f(p2[E1], p2[E2]);
	glEnd();
}

template<typename T>
void drawLine(const Mvec<T> &pp) {
	if (pp.norm()*pp.norm() > 0) {
		Mvec<T> p1 = (pp + sqrt(pp*pp)) / (-ei<double>()|pp);
		Mvec<T> p2 = (pp - sqrt(pp*pp)) / (-ei<double>()|pp);
		glBegin(GL_LINES);
			glVertex2f(p1[E1], p1[E2]);
			glVertex2f(p2[E1], p2[E2]);
		glEnd();
	}
}

template<typename T>
void drawCircle(const Mvec<T> &center, float r, int num_segments = 256) {
	float cx = center[E1];
	float cy = center[E2];
	float theta = 2 * 3.1415926 / float(num_segments);
	float tangetial_factor = tanf(theta); // Calculate the tangential factor
	float radial_factor = cosf(theta); // Calculate the radial factor
	float x = r; // We start at angle = 0
	float y = 0;

	glBegin(GL_LINE_LOOP);
	for(int ii = 0; ii < num_segments; ii++) {
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

}

#endif
