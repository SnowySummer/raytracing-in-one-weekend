#ifndef TEXTURE__SOLIDCOLORTEXTURE_HPP
#define TEXTURE__SOLIDCOLORTEXTURE_HPP

#include "Texture.hpp"

#include <common/vec4.hpp>

class SolidColorTexture : public Texture {
public:
    vec4 albedo;

public:
    // SolidColorTexture constructor
    SolidColorTexture() : albedo(vec4(0.0f, 0.0f, 0.0f)) {}
    SolidColorTexture(vec4 _albedo) : albedo(_albedo) {}

    // Texture value
    vec4 value(float u, float v, vec4 p) override {
        return albedo;
    }
};

#endif