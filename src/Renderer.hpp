#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <Framebuffer.hpp>
#include <Camera/Camera.hpp>
#include <Hittable/Hittable.hpp>
#include <cstdio>
#include <memory>

class Renderer {
public:
    int samples_per_pixel;

public:
    // Renderer constructor
    Renderer() : samples_per_pixel(1) {}

    // Main render function
    void render(Framebuffer& framebuffer, const std::shared_ptr<Camera> camera, std::shared_ptr<Hittable>& world) {
        // Per-pixel rendering
        for (int y = 0; y < framebuffer.height; y++) {
            // Render line
            for (int x = 0; x < framebuffer.width; x++) {
                // Accumulate color
                vec4 color = vec4(0.0f, 0.0f, 0.0f);
                for (int i = 0; i < samples_per_pixel; i++) {
                    Ray ray = camera->gen_ray(x, y);
                    color += this->ray_value(ray, world);
                }
                color /= samples_per_pixel;
                framebuffer.get(x, y) = color;
            }
        }
    }

private:
    // Get ray value
    vec4 ray_value(Ray ray, std::shared_ptr<Hittable>& world) {
        // Check hit
        HitRecord record;
        if (!world->ray_hit(ray, Interval(0, INFINITY), record)) {
            // Render background
            float t = 0.5f * (1.0f + ray.direction[1]);
            return (1.0f - t) * vec4(1.0f, 1.0f, 1.0f) + t * vec4(0.5f, 0.7f, 1.0f);
        }

        // Render hittable
        return 0.5f * (vec4(1.0f, 1.0f, 1.0f) + record.n);
    }
};

#endif