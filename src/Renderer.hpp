#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/PRNG.hpp>
#include <common/Ray.hpp>
#include <Framebuffer.hpp>
#include <Camera/Camera.hpp>
#include <Material/Material.hpp>
#include <Hittable/Hittable.hpp>
#include <HitRecord.hpp>
#include <ScatterRecord.hpp>
#include <cstdio>
#include <memory>

class Renderer {
public:
    PRNG prng;
    int samples_per_pixel;
    int ray_maxdepth;

public:
    // Renderer constructor
    Renderer() : prng(), samples_per_pixel(1), ray_maxdepth(1) {}

    // Main render function
    void render(Framebuffer& framebuffer, const std::shared_ptr<Camera> camera, std::shared_ptr<Hittable>& world) {
        // Per-pixel rendering
        for (int y = 0; y < framebuffer.height; y++) {
            // Log line
            printf("\e[0K\r[RENDER] line %d/%d", y+1, framebuffer.height);

            // Render line
            for (int x = 0; x < framebuffer.width; x++) {
                // Accumulate color
                vec4 color = vec4(0.0f, 0.0f, 0.0f);
                for (int i = 0; i < samples_per_pixel; i++) {
                    Ray ray = camera->gen_ray(x, y);
                    color += this->ray_value(ray, ray_maxdepth, world);
                }
                color /= samples_per_pixel;

                // Update framebuffer
                framebuffer.get(x, y) = color;
            }
        }

        printf("\e[0K\r[RENDER] finished\n");
    }

private:
    // Get ray value
    vec4 ray_value(Ray ray, int ray_depth, std::shared_ptr<Hittable>& world) {
        // Recursion check
        if (ray_depth <= 0) return vec4(0.0f, 0.0f, 0.0f);
        
        // Check hit
        HitRecord record;
        if (!world->ray_hit(ray, Interval(1e-3f, INFINITY), record)) {
            // Render background
            float t = 0.5f * (1.0f + ray.direction[1]);
            return (1.0f - t) * vec4(1.0f, 1.0f, 1.0f) + t * vec4(0.5f, 0.7f, 1.0f);
        }

        // Perform scattering
        ScatterRecord srecord;
        if (!record.mat->ray_scatter(prng, ray, record, srecord)) return vec4(0.0f, 0.0f, 0.0f);

        // Render hittable
        return srecord.attenuation * ray_value(srecord.scatter_ray, ray_depth-1, world);
    }
};

#endif