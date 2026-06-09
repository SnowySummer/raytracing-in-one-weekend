#ifndef SCENE__RTIOW__SCENE2_HPP
#define SCENE__RTIOW__SCENE2_HPP

#include <Scene/Scene.hpp>

#include <Camera/PinholeCamera.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/Geometry.hpp>
#include <Material/Dielectric.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Material.hpp>
#include <Material/Metal.hpp>
#include <Renderer/RendererSkyBackground.hpp>

namespace RTIOW {

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
        std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
        pinhole_camera->prng.set_seed(PRNG_SEED);
        pinhole_camera->eye = vec4(-2.0f, 2.0f, 1.0f);
        pinhole_camera->direction = vec4(2.0f, -2.0f, -2.0f);
        pinhole_camera->setup(framebuffer);
        camera = pinhole_camera;
    }

    void init_world() override {
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
};

}

#endif