#ifndef IO__FRAMEBUFFEREXPORT_HPP
#define IO__FRAMEBUFFEREXPORT_HPP

#include <Framebuffer.hpp>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

class FramebufferExport {
public:
    // Export to PNG
    static bool to_png(const Framebuffer& framebuffer, std::string filepath) {
        // Extract raw colorbuffer
        std::vector<uint8_t> colorbuffer_raw = std::vector<uint8_t>(3 * framebuffer.size());
        for (int i = 0; i < framebuffer.size(); i++) {
            colorbuffer_raw[3*i]     = std::min(int(256.0f * framebuffer[i][0]), 255);
            colorbuffer_raw[3*i + 1] = std::min(int(256.0f * framebuffer[i][1]), 255);
            colorbuffer_raw[3*i + 2] = std::min(int(256.0f * framebuffer[i][2]), 255);
        }

        // Perform write to filesystem
        int err = stbi_write_png(
            filepath.c_str(),
            framebuffer.width, framebuffer.height, 3,
            colorbuffer_raw.data(),
            framebuffer.width * 3 * sizeof(uint8_t)
        );

        // Error handling
        if (err == 0) {
            fprintf(stderr, "FramebufferExport::to_png error: Unable to write PNG file to ./%s\n", filepath.c_str());
            return false;
        }

        return true;
    }
};

#endif