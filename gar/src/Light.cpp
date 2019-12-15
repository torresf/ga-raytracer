#include <iostream>
#include "gar/Light.hpp"

namespace gar {

Light::Light()
  :_size(50.f), _pos(glm::vec2(0.f, 0.f))
{}

Light::Light(const float size, const glm::vec2 &pos)
  :_size(size), _pos(pos)
{}

}
