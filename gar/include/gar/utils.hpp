/*
 * Author : Florian TORRES
 * Date : March 2020
 */

#pragma once
#ifndef __UTILS__HPP
#define __UTILS__HPP

namespace gar {

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

const float easeIn(const float t, const float b, const float c, const float d) {
	return c*(t/d)*t + b;
}

} // namespace gar

#endif
