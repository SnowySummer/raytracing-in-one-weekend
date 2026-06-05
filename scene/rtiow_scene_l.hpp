#ifndef SCENE__RTIOW_SCENE_L_HPP
#define SCENE__RTIOW_SCENE_L_HPP

#include <Framebuffer.hpp>
#include <Camera/Camera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Material/Material.hpp>
#include <Material/Lambertian.hpp>
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
    std::shared_ptr<Material> sphere_mat = std::make_shared<Lambertian>(vec4(0.1f, 0.2f, 0.5f));

    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, -100.5f, -1.0f), 100.0f, ground_mat));
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, 0.0f, -1.0f), 0.5f, sphere_mat));
    world = hittable_l;
}

#endif