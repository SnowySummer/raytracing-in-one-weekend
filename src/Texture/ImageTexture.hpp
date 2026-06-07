#ifndef TEXTURE__IMAGETEXTURE_HPP
#define TEXTURE__IMAGETEXTURE_HPP

#include "Texture.hpp"

#include <common/Interval.hpp>
#include <io/FramebufferImport.hpp>
#include <Framebuffer.hpp>
#include <string>

class ImageTexture : public Texture {
public:
    Framebuffer image;

public:
    // ImageTexture constructor
    ImageTexture() {}
    ImageTexture(std::string filepath) {
        FramebufferImport::load(image, filepath);
    }

    // Texture value
    vec4 value(float u, float v, vec4 p) override {
        // Clamp u,v values
        u = Interval(0, 1).clamp(u);
        v = 1.0f - Interval(0, 1).clamp(v);

        // Quantise u,v values
        int i = int(u * image.width);
        int j = int(v * image.height);
        return image.get(i, j);
    }
};

#endif