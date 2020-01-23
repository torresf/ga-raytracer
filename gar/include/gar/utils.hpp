#pragma once
#ifndef __UTILS__HPP
#define __UTILS__HPP

namespace gar {

float lerp(float a, float b, float t) {
	return a + t * (b - a);
}

float easeIn(float t, float b, float c, float d) {
	return c*(t/d)*t + b;
}

}

#endif
