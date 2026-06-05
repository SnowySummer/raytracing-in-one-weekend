#ifndef SCENE__RTIOW_SCENE_L_HPP
#define SCENE__RTIOW_SCENE_L_HPP

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

void rtiow_scene1(
    Renderer& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Hittable>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer.prng.set_seed(prng_seed);
    renderer.samples_per_pixel = 100;
    renderer.ray_maxdepth = 10;

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

    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = hittable_l;
}

void rtiow_scene2(
    Renderer& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Hittable>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer.prng.set_seed(prng_seed);
    renderer.samples_per_pixel = 100;
    renderer.ray_maxdepth = 10;

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

    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = hittable_l;
}

void rtiow_scene3(
    Renderer& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Hittable>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer.prng.set_seed(prng_seed);
    renderer.samples_per_pixel = 100;
    renderer.ray_maxdepth = 10;

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

    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = hittable_l;
}

void rtiow_scene4(
    Renderer& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Hittable>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;

    // Setup renderer
    renderer.prng.set_seed(prng_seed);
    renderer.samples_per_pixel = 100;
    renderer.ray_maxdepth = 10;

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

    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 0.0f,    0.0f, -1.2f), 0.5f, center_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.5f, left_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(-1.0f,    0.0f, -1.0f), 0.4f, bubble_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4( 1.0f,    0.0f, -1.0f), 0.5f, right_mat));

    world = hittable_l;
}

#endif