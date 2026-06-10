#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/PRNG.hpp>
#include <common/Ray.hpp>
#include <Framebuffer.hpp>
#include <Camera/Camera.hpp>
#include <Material/Material.hpp>
#include <Geometry/Geometry.hpp>
#include <PDF/GeometryPDF.hpp>
#include <PDF/MixturePDF.hpp>
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
    void render(Framebuffer& framebuffer, const std::shared_ptr<Camera> camera, std::shared_ptr<Geometry>& world, bool use_light, std::shared_ptr<Geometry> light_hint) {
        // Per-pixel rendering
        for (int y = 0; y < framebuffer.height; y++) {
            // Log line
            printf("\e[2K\r[RENDER] line %d/%d", y+1, framebuffer.height);

            // Render line
            for (int x = 0; x < framebuffer.width; x++) {
                // Accumulate color
                vec4 color = vec4(0.0f, 0.0f, 0.0f);
                for (int i = 0; i < samples_per_pixel; i++) {
                    Ray ray = camera->gen_ray(x, y);
                    color += this->ray_value(ray, ray_maxdepth, world, use_light, light_hint);
                }
                color /= samples_per_pixel;

                // Update framebuffer
                framebuffer.get(x, y) = color;
            }
        }

        printf("\e[2K\r[RENDER] finished\n");
    }

private:
    // Get ray value
    vec4 ray_value(Ray ray, int ray_depth, std::shared_ptr<Geometry>& world, bool use_light, std::shared_ptr<Geometry> light_hint) {
        // Recursion check
        if (ray_depth <= 0) return vec4(0.0f, 0.0f, 0.0f);
        
        // Check hit
        HitRecord record;
        if (!world->ray_hit(prng, ray, Interval(1e-3f, INFINITY), record)) {
            // Render background
            return background(ray);
        }

        // Keep emitted light
        vec4 light_emit = record.mat->light_emission(ray, record, record.u, record.v, record.p);

        // Perform scattering
        ScatterRecord srecord;
        if (!record.mat->ray_scatter(prng, ray, record, srecord)) {
            return light_emit;
        }

        // If no PDF, directly go to next ray
        if (srecord.skip_pdf) {
            vec4 scatter_value = srecord.attenuation * ray_value(srecord.scatter_ray, ray_depth-1, world, use_light, light_hint);
            return light_emit + scatter_value;
        }

        // Generate mixture PDF
        std::shared_ptr<PDF> final_pdf;
        if (use_light) {
            final_pdf = std::make_shared<MixturePDF>(srecord.pdf, std::make_shared<GeometryPDF>(record.p, light_hint));
        } else {
            final_pdf = srecord.pdf;
        }

        // Generate scattered ray
        Ray scatter_ray = Ray(record.p, final_pdf->generate(prng), ray.time);

        // Calcualte PDF
        float scatter_pdf = record.mat->scatter_pdf(ray, record, scatter_ray);
        float pdf_value = final_pdf->value(prng, scatter_ray.direction);

        // Render geometry
        vec4 scatter_value = srecord.attenuation * scatter_pdf * ray_value(scatter_ray, ray_depth-1, world, use_light, light_hint) / pdf_value;
        return light_emit + scatter_value;
    }

    virtual vec4 background(Ray ray) = 0;
};

#endif