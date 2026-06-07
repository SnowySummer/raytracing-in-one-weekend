#ifndef TEXTURE__NOISETEXTURE_HPP
#define TEXTURE__NOISETEXTURE_HPP

#include "Texture.hpp"

#include <Perlin.hpp>

class NoiseTexture : public Texture {
public:
    Perlin perlin;
    float scale;

public:
    // NoiseTexture constructor
    NoiseTexture() : scale(1.0f) {}
    NoiseTexture(PRNG& prng) : perlin(Perlin(prng)), scale(1.0f) {}
    NoiseTexture(PRNG& prng, float _scale) : perlin(Perlin(prng)), scale(_scale) {}

    // Texture value
    vec4 value(float u, float v, vec4 p) override {
        return perlin.turb(scale * p, 7) * vec4(1.0f, 1.0f, 1.0f);
        // return 0.5f * (1.0f + perlin.noise(scale * p)) * vec4(1.0f, 1.0f, 1.0f);
    }

};

#endif