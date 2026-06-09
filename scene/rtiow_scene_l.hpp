#ifndef SCENE__RTIOW_SCENE_L_HPP
#define SCENE__RTIOW_SCENE_L_HPP

#include <common/vec4.hpp>
#include <common/PRNG.hpp>
#include <Camera/Camera.hpp>
#include <Camera/LensCamera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/Geometry.hpp>
#include <Material/Dielectric.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Material.hpp>
#include <Material/Metal.hpp>
#include <Renderer/RendererSkyBackground.hpp>
#include <Framebuffer.hpp>
#include <cstdint>
#include <memory>

void rtiow_scene1(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Material> center_mat = std::make_shared<Lambertian>(vec4(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Material> left_mat   = std::make_shared<Dielectric>(1.50f);
    std::shared_ptr<Material> bubble_mat = std::make_shared<Dielectric>(1.0f / 1.50f);
    std::shared_ptr<Material> right_mat  = std::make_shared<Metal>(vec4(0.8f, 0.6f, 0.2f), 1.0f);

    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = geometry_l;
}

void rtiow_scene2(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(-2.0f, 2.0f, 1.0f);
    pinhole_camera->direction = vec4(2.0f, -2.0f, -2.0f);
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Material> center_mat = std::make_shared<Lambertian>(vec4(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Material> left_mat   = std::make_shared<Dielectric>(1.50f);
    std::shared_ptr<Material> bubble_mat = std::make_shared<Dielectric>(1.0f / 1.50f);
    std::shared_ptr<Material> right_mat  = std::make_shared<Metal>(vec4(0.8f, 0.6f, 0.2f), 1.0f);

    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = geometry_l;
}

void rtiow_scene3(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(-2.0f, 2.0f, 1.0f);
    pinhole_camera->direction = vec4(2.0f, -2.0f, -2.0f);
    pinhole_camera->vfov = 1.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Material> center_mat = std::make_shared<Lambertian>(vec4(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Material> left_mat   = std::make_shared<Dielectric>(1.50f);
    std::shared_ptr<Material> bubble_mat = std::make_shared<Dielectric>(1.0f / 1.50f);
    std::shared_ptr<Material> right_mat  = std::make_shared<Metal>(vec4(0.8f, 0.6f, 0.2f), 1.0f);

    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = geometry_l;
}

void rtiow_scene4(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<LensCamera> lens_camera = std::make_shared<LensCamera>();
    lens_camera->prng.set_seed(prng_seed);
    lens_camera->eye = vec4(-2.0f, 2.0f, 1.0f);
    lens_camera->direction = vec4(2.0f, -2.0f, -2.0f);
    lens_camera->vfov = 1.0f / 9.0f * M_PI;
    lens_camera->defocus_angle = 1.0f / 18.0f * M_PI;
    lens_camera->focal_distance = 3.4f;
    lens_camera->setup(framebuffer);
    camera = lens_camera;

    // Setup scene
    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.8f, 0.8f, 0.0f));
    std::shared_ptr<Material> center_mat = std::make_shared<Lambertian>(vec4(0.1f, 0.2f, 0.5f));
    std::shared_ptr<Material> left_mat   = std::make_shared<Dielectric>(1.50f);
    std::shared_ptr<Material> bubble_mat = std::make_shared<Dielectric>(1.0f / 1.50f);
    std::shared_ptr<Material> right_mat  = std::make_shared<Metal>(vec4(0.8f, 0.6f, 0.2f), 1.0f);

    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = geometry_l;
}

void rtiow_scene5(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

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
            vec4 sphere_center = vec4(a + 0.9f*prng.randf(), 0.2f, b + 0.9f * prng.randf());
            if ((sphere_center - vec4(4.0f, 0.2f, 0.0f)).len() < 0.9f) continue;

            // Choose sphere material
            float choose_mat = prng.randf();
            std::shared_ptr<Material> sphere_mat;
            if (choose_mat < 0.8f) {
                vec4 albedo = prng.color() * prng.color();
                sphere_mat = std::make_shared<Lambertian>(albedo);
            } else if (choose_mat < 0.9f) {
                vec4 albedo = 0.5f * (vec4(1.0f, 1.0f, 1.0f) + prng.color());
                float fuzz = 0.5f * prng.randf();
                sphere_mat = std::make_shared<Metal>(albedo, fuzz);
            } else {
                sphere_mat = std::make_shared<Dielectric>(1.5f);
            }

            // Add sphere
            geometry_l->add(std::make_shared<Sphere>(sphere_center, 0.2f, sphere_mat));
        }
    }

    world = geometry_l;
}

#endif