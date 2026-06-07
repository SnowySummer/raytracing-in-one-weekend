#ifndef RENDERER__RENDERERSOLIDBACKGROUND_HPP
#define RENDERER__RENDERERSOLIDBACKGROUND_HPP

#include "Renderer.hpp"

class RendererSolidBackground : public Renderer {
public:
    vec4 background_color;

public:
    // RendererSolidBackground constructor
    RendererSolidBackground() : background_color(vec4(0.0f, 0.0f, 0.0f)) {}
    RendererSolidBackground(vec4 _background_color) :
    background_color(_background_color) {}

    vec4 background(Ray ray) override {
        return background_color;
    }
};

#endif