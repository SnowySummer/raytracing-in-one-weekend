#ifndef SCENE__RTIOW_SCENE_L_HPP
#define SCENE__RTIOW_SCENE_L_HPP

#include <Framebuffer.hpp>
#include <Camera/Camera.hpp>
#include <Camera/PinholeCamera.hpp>
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
    PRNG prng;
    prng.set_seed(1337);

    // Setup renderer
    renderer.samples_per_pixel = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng.rand());
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, 0.0f, -1.0f), 0.5f));
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, -100.5f, -1.0f), 100.0f));
    world = hittable_l;
}

#endif