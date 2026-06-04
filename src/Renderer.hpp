#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vec4.hpp>
#include <Ray.hpp>

#include <Framebuffer.hpp>
#include <Camera.hpp>
#include <Hittable/Sphere.hpp>

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

                // Check hit
                vec4 color = vec4(0.0f, 0.0f, 0.0f);
                Sphere sphere = Sphere(vec4(0.0f, 0.0f, -1.0f), 0.5f);
                HitRecord record;
                if (!sphere.ray_hit(ray, Interval(0, INFINITY), record)) {
                    // Render background
                    float t = 0.5f * (1.0f + ray.direction[1]);
                    color = (1.0f - t) * vec4(1.0f, 1.0f, 1.0f) + t * vec4(0.5f, 0.7f, 1.0f);
                } else {
                    color = 0.5f * (vec4(1.0f, 1.0f, 1.0f) + record.n);
                }

                framebuffer.get(x, y) = color;
            }
        }
    }
};

#endif