#ifndef SCENE__RTTNW__SCENE2_HPP
#define SCENE__RTTNW__SCENE2_HPP

#include "../Scene.hpp"

#include <Camera/LensCamera.hpp>
#include <Geometry/collection/BVH.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/Geometry.hpp>
#include <Material/Dielectric.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Material.hpp>
#include <Material/Metal.hpp>
#include <Renderer/RendererSkyBackground.hpp>

namespace RTTNW {

class Scene2 : public Scene {

public:
    static constexpr uint32_t PRNG_SEED = 1337;
public:
    void init_framebuffer() override {
        framebuffer = Framebuffer(400, 225);
    }

    void init_renderer() override {
        renderer = std::make_shared<RendererSkyBackground>();
        renderer->prng.set_seed(PRNG_SEED);
        renderer->samples_per_pixel = 100;
        renderer->ray_maxdepth = 10;
    }

    void init_camera() override {
        std::shared_ptr<LensCamera> lens_camera = std::make_shared<LensCamera>();
        lens_camera->prng.set_seed(PRNG_SEED);
        lens_camera->eye = vec4(13.0f, 2.0f, 3.0f);
        lens_camera->direction = vec4(-13.0f, -2.0f, -3.0f);
        lens_camera->vfov = 1.0f / 9.0f * M_PI;
        lens_camera->defocus_angle = 1.0f / 300.0f * M_PI;
        lens_camera->focal_distance = 10.0f;
        lens_camera->setup(framebuffer);
        camera = lens_camera;
    }

    void init_world() override {
        // Scene PRNG
        PRNG prng = PRNG(PRNG_SEED);

        // Setup scene
        std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

        std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.5f, 0.5f, 0.5f));
        geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, -1.0f), 1000.0f, ground_mat));

        std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
        std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(vec4(0.4f, 0.2f, 0.1f));
        std::shared_ptr<Material> material3 = std::make_shared<Metal>(vec4(0.7f, 0.6f, 0.5f));
        geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, 1.0f, 0.0f), 1.0f, material1));
        geometry_l->add(std::make_shared<Sphere>(vec4(-4.0f, 1.0f, 0.0f), 1.0f, material2));
        geometry_l->add(std::make_shared<Sphere>(vec4( 4.0f, 1.0f, 0.0f), 1.0f, material3));

        for (int a = -11; a < 11; a++) {
            for (int b = -11; b < 11; b++) {
                // Choose sphere center
                vec4 sphere_center1 = vec4(a + 0.9f*prng.randf(), 0.2f, b + 0.9f * prng.randf());
                if ((sphere_center1 - vec4(4.0f, 0.2f, 0.0f)).len() < 0.9f) continue;
                vec4 sphere_center2 = sphere_center1;

                // Choose sphere material
                float choose_mat = prng.randf();
                std::shared_ptr<Material> sphere_mat;
                if (choose_mat < 0.8f) {
                    vec4 albedo = prng.color() * prng.color();
                    sphere_mat = std::make_shared<Lambertian>(albedo);

                    sphere_center2 = sphere_center1 + vec4(0.0f, prng.randf(0.0f, 0.5f), 0.0f);
                } else if (choose_mat < 0.9f) {
                    vec4 albedo = 0.5f * (vec4(1.0f, 1.0f, 1.0f) + prng.color());
                    float fuzz = 0.5f * prng.randf();
                    sphere_mat = std::make_shared<Metal>(albedo, fuzz);
                } else {
                    sphere_mat = std::make_shared<Dielectric>(1.5f);
                }

                // Add sphere
                geometry_l->add(std::make_shared<Sphere>(sphere_center1, sphere_center2, 0.2f, sphere_mat));
            }
        }

        std::shared_ptr<BVH> world_bvh = std::make_shared<BVH>(geometry_l);

        world = world_bvh;
    }

    void init_light_hint() override {
        use_light = false;
    }
};

}

#endif