#ifndef POSTPROCESSING_HPP
#define POSTPROCESSING_HPP

#include <Framebuffer.hpp>

class PostProcessing {
public:
    // Gamma correction
    static void gamma(Framebuffer& framebuffer, float gamma) {
        for (int i = 0; i < framebuffer.size(); i++) {
            framebuffer[i][0] = std::pow(framebuffer[i][0], gamma);
            framebuffer[i][1] = std::pow(framebuffer[i][1], gamma);
            framebuffer[i][2] = std::pow(framebuffer[i][2], gamma);
        }
    }
};

#endif