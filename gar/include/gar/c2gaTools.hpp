/*
 * Author : Florian TORRES
 * Date : March 2020
 */

#pragma once
#ifndef __C2GATOOLS__HPP
#define __C2GATOOLS__HPP

using namespace c2ga;

namespace gar {

// Create point from x, y coords
template<typename T>
Mvec<T> point(const T &x, const T &y){

	Mvec<T> mv;
	mv[E1] = x;
	mv[E2] = y;
	mv[Ei] = 0.5 * mv.quadraticNorm();
	mv[E0] = 1.0;

	return mv;
}

// Create point from vec2
Mvec<double> point(glm::vec2 &vec){
	return point((double) vec.x, (double) vec.y);
}

// Create line from two points
template<typename T>
Mvec<T> line(const Mvec<T> &p1, const Mvec<T> &p2) {
	return p1 ^ p2 ^ ei<T>();
}

// Create line from equation ax + by + c = 0
template<typename T>
Mvec<T> line(const T &a, const T &b, const T &c) {
	return a * e1<T>() + b * e2<T>() + c * ei<T>();
}

// Create circle from center (x, y coords) and radius
template<typename T>
Mvec<T> circle(const T &x, const T &y, const T &r) {
	Mvec<T> dualCircle = point(x, y);
	dualCircle[c2ga::Ei] -= r * r * .5;
	return !dualCircle; // = circle
}

// Normalize multivector
template<typename T>
Mvec<T> normalize(const Mvec<T> &mv) {
	return -mv / (mv | ei<double>());
}

// Get intersection between to multivectors
template<typename T>
Mvec<T> getIntersection(const Mvec<T> &mv1, const Mvec<T> &mv2) {
	return !((!mv1) ^ (!mv2)); // Intersection
}

// Returns true if the two multivectors are intersected
template<typename T>
bool areIntersected(const Mvec<T> &mv1, const Mvec<T> &mv2) {
	return (T)(getIntersection(mv1, mv2) | getIntersection(mv1, mv2)) > 0;
}

// Returns true if the point p is in circle c
template<typename T>
bool isPointInCircle(const Mvec<T> &p, const Mvec<T> &c) {
	T distToCircle = (!p) | c;
	return distToCircle > 0;
}

// Returns the projection (a point) of the point p on the line l.
template<typename T>
Mvec<T> projectPointOnLine(const Mvec<T> &p, const Mvec<T> &l) {
	return -normalize(p < l);
}

// Get the center (a point) of the circle
template<typename T>
Mvec<T> getCenterOfCircle(const Mvec<T> &circle) {
	return -circle / (ei<T>() < circle);
}

// Get the first point from a point pair
template<typename T>
Mvec<T> getFirstPointFromPointPair(const Mvec<T> &pp) {
	return (pp + sqrt(pp*pp)) / (-ei<T>() | pp);
}

// Get the second point from a point pair
template<typename T>
Mvec<T> getSecondPointFromPointPair(const Mvec<T> &pp) {
	return (pp - sqrt(pp*pp)) / (-ei<T>() | pp);
}

// Project a point on a circle and returns the projection
template<typename T>
Mvec<T> projectPointOnCircle(const Mvec<T> &p, const Mvec<T> &c) {
	return getFirstPointFromPointPair(getIntersection(c, line(p, getCenterOfCircle(c))));
}

// Get the distance between two multivectors
template<typename T>
float distance(const Mvec<T> &p1, const Mvec<T> &p2) {
	return (p2 - p1).norm();
}

} // namespace gar

#endif
