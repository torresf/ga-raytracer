/*
 * Author : Florian TORRES
 * Date : March 2020
 */

#pragma once
#ifndef __LIGHT__HPP
#define __LIGHT__HPP

#include <glimac/glm.hpp>

namespace gar {

class Light {

  public:
    // Constructor
    Light();
    Light(const float size, const float maxSize, const glm::vec2 &pos);

    // Getters
    const float& size() const { return _size; }
    const float &maxSize() const { return _maxSize; }
    const glm::vec2& pos() const { return _pos; }

    // Setters
    float& size() { return _size; }
    float &maxSize() { return _maxSize; }
    glm::vec2& pos() { return _pos; }

  private:
    float _size;
    float _maxSize;
    glm::vec2 _pos;

};

} // namespace gar

#endif
