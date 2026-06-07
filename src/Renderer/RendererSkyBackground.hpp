#ifndef RENDERER__RENDERERSKYBACKGROUND_HPP
#define RENDERER__RENDERERSKYBACKGROUND_HPP

#include "Renderer.hpp"

class RendererSkyBackground : public Renderer {
public:
    vec4 background(Ray ray) override {
        float t = 0.5f * (1.0f + ray.direction[1]);
        return (1.0f - t) * vec4(1.0f, 1.0f, 1.0f) + t * vec4(0.5f, 0.7f, 1.0f);
    }
};

#endif