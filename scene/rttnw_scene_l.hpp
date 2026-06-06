#ifndef SCENE__RTTNW_SCENE_L_HPP
#define SCENE__RTTNW_SCENE_L_HPP

#include <Renderer.hpp>
#include <Framebuffer.hpp>
#include <Camera/Camera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Camera/LensCamera.hpp>
#include <Material/Material.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Metal.hpp>
#include <Material/Dielectric.hpp>
#include <Hittable/Hittable.hpp>
#include <Hittable/HittableList.hpp>
#include <Hittable/Sphere.hpp>
#include <memory>

void rttnw_scene1(
    Renderer& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Hittable>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer.prng.set_seed(prng_seed);
    renderer.samples_per_pixel = 100;
    renderer.ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<LensCamera> lens_camera = std::make_shared<LensCamera>();
    lens_camera->prng.set_seed(prng_seed);
    lens_camera->eye = vec4(13.0f, 2.0f, 3.0f);
    lens_camera->direction = vec4(-13.0f, -2.0f, -3.0f);
    lens_camera->vfov = 1.0f / 9.0f * M_PI;
    lens_camera->defocus_angle = 1.0f / 300.0f * M_PI;
    lens_camera->focal_distance = 10.0f;
    lens_camera->setup(framebuffer);
    camera = lens_camera;

    // Setup scene
    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();

    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.5f, 0.5f, 0.5f));
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, -1.0f), 1000.0f, ground_mat));

    std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(vec4(0.4f, 0.2f, 0.1f));
    std::shared_ptr<Material> material3 = std::make_shared<Metal>(vec4(0.7f, 0.6f, 0.5f));
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f, 1.0f, 0.0f), 1.0f, material1));
    hittable_l->add(std::make_shared<Sphere>(vec4(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    hittable_l->add(std::make_shared<Sphere>(vec4( 4.0f, 1.0f, 0.0f), 1.0f, material3));

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
            hittable_l->add(std::make_shared<Sphere>(sphere_center1, sphere_center2, 0.2f, sphere_mat));
        }
    }

    world = hittable_l;
}

#endif