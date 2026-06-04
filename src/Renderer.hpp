#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <Framebuffer.hpp>
#include <Camera.hpp>

class Renderer {
public:
    // Renderer constructor
    Renderer() {}

    // Main render function
    void render(Framebuffer& framebuffer, const Camera camera) {
        // Per-pixel rendering
        for (int y = 0; y < framebuffer.height; y++) {
            for (int x = 0; x < framebuffer.width; x++) {
                // Generate ray
                Ray ray = camera.gen_ray(x, y);

                // Render ray
                float t = 0.5f * (1.0f + ray.direction[1]);
                framebuffer.get(x, y) = (1.0f - t) * vec4(1.0f, 1.0f, 1.0f) + t * vec4(0.5f, 0.7f, 1.0f);
            }
        }
    }
};

#endif