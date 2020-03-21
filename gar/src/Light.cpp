/*
 * Author : Florian TORRES
 * Date : March 2020
 */

#include <iostream>
#include "gar/Light.hpp"

namespace gar {

Light::Light()
    : _size(64.f), _maxSize(512.f), _pos(glm::vec2(0.f, 0.f))
{}

Light::Light(const float size, const float maxSize, const glm::vec2 &pos)
    : _size(size), _maxSize(maxSize), _pos(pos)
{}

} // namespace gar
