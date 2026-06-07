#ifndef TEXTURE__CHECKERBOARDTEXTURE_HPP
#define TEXTURE__CHECKERBOARDTEXTURE_HPP

#include "Texture.hpp"

#include <common/vec4.hpp>
#include <Texture/SolidColorTexture.hpp>
#include <memory>

class CheckerBoardTexture : public Texture {
public:
    float scale;
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;

public:
    // CheckerBoardTexture constructor
    CheckerBoardTexture() :
    scale(1.0f),
    odd(std::make_shared<SolidColorTexture>(vec4(0.0f, 0.0f, 0.0f))),
    even(std::make_shared<SolidColorTexture>(vec4(1.0f, 1.0f, 1.0f))) {}
    CheckerBoardTexture(float _scale, vec4 _odd, vec4 _even) :
    scale(_scale),
    odd(std::make_shared<SolidColorTexture>(_odd)),
    even(std::make_shared<SolidColorTexture>(_even)) {}

    // Texture value
    vec4 value(float u, float v, vec4 p) override {
        int x_i = int(std::floor(p[0] / scale));
        int y_i = int(std::floor(p[1] / scale));
        int z_i = int(std::floor(p[2] / scale));
        return (((x_i + y_i + z_i) % 2) == 0) ? even->value(u, v, p) : odd->value(u, v, p);
    }
};

#endif