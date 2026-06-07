#ifndef TEXTURE__TEXTURE_HPP
#define TEXTURE__TEXTURE_HPP

#include <common/vec4.hpp>

class Texture {
public:
    // Texture virtual destructor
    virtual ~Texture() {}

    // Texture value
    virtual vec4 value(float u, float v, vec4 p) = 0;
};

#endif