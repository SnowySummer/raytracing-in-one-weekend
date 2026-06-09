#ifndef SCENE__RTTNW__SCENE6_HPP
#define SCENE__RTTNW__SCENE6_HPP

#include "../Scene.hpp"

#include <Camera/LensCamera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Geometry/collection/BVH.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Quad.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/Geometry.hpp>
#include <Material/Dielectric.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Material.hpp>
#include <Material/Metal.hpp>
#include <Renderer/RendererSkyBackground.hpp>
#include <Texture/CheckerBoardTexture.hpp>
#include <Texture/ImageTexture.hpp>
#include <Texture/NoiseTexture.hpp>

namespace RTTNW {

class Scene6 : public Scene {
public:
    static constexpr uint32_t PRNG_SEED = 1337;

public:
    void init_framebuffer() override {
        framebuffer = Framebuffer(400, 400);
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
        pinhole_camera->eye = vec4(0.0f, 0.0f, 9.0f);
        pinhole_camera->direction = vec4(0.0f, 0.0f, -9.0f);
        pinhole_camera->vfov = 4.0f / 9.0f * M_PI;
        pinhole_camera->setup(framebuffer);
        camera = pinhole_camera;
    }

    void init_world() override {
        // Scene PRNG
        PRNG prng = PRNG(PRNG_SEED);

        // Setup scene
        std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

        std::shared_ptr<Material> left_red     = std::make_shared<Lambertian>(vec4(1.0f, 0.2f, 0.2f));
        std::shared_ptr<Material> back_green   = std::make_shared<Lambertian>(vec4(0.2f, 1.0f, 0.2f));
        std::shared_ptr<Material> right_blue   = std::make_shared<Lambertian>(vec4(0.2f, 0.2f, 1.0f));
        std::shared_ptr<Material> upper_orange = std::make_shared<Lambertian>(vec4(1.0f, 0.5f, 0.0f));
        std::shared_ptr<Material> lower_teal   = std::make_shared<Lambertian>(vec4(0.2f, 0.8f, 0.8f));

        geometry_l->add(std::make_shared<Quad>(vec4(-3.0f, -2.0f, 5.0f), vec4(0.0f, 0.0f, -4.0f), vec4(0.0f, 4.0f,  0.0f), left_red));
        geometry_l->add(std::make_shared<Quad>(vec4(-2.0f, -2.0f, 0.0f), vec4(4.0f, 0.0f,  0.0f), vec4(0.0f, 4.0f,  0.0f), back_green));
        geometry_l->add(std::make_shared<Quad>(vec4( 3.0f, -2.0f, 1.0f), vec4(0.0f, 0.0f,  4.0f), vec4(0.0f, 4.0f,  0.0f), right_blue));
        geometry_l->add(std::make_shared<Quad>(vec4(-2.0f,  3.0f, 1.0f), vec4(4.0f, 0.0f,  0.0f), vec4(0.0f, 0.0f,  4.0f), upper_orange));
        geometry_l->add(std::make_shared<Quad>(vec4(-2.0f, -3.0f, 5.0f), vec4(4.0f, 0.0f,  0.0f), vec4(0.0f, 0.0f, -4.0f), lower_teal));
        world = geometry_l;
    }
};

}

#endif