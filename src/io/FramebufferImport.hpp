#ifndef IO__FRAMEBUFFERIMPORT_HPP
#define IO__FRAMEBUFFERIMPORT_HPP

#include <Framebuffer.hpp>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

class FramebufferImport {
public:
    // Export to PNG
    static bool load(Framebuffer& framebuffer, std::string filepath) {
        int x;
        int y;
        int n;

        unsigned char* data = stbi_load(filepath.c_str(), &x, &y, &n, 3);
        if (data == NULL) {
            fprintf(stderr, "FramebufferImport::load error: Unable to load image ./%s\n", filepath.c_str());
            return false;
        }

        framebuffer = Framebuffer(x, y);
        for (int i = 0; i < x * y; i++) {
            framebuffer[i] = vec4(
                data[3*i] / 256.0f,
                data[3*i+1] / 256.0f,
                data[3*i+2] / 256.0f,
                0.0f
            );
        }

        stbi_image_free(data);
        return true;
    }
};

#endif