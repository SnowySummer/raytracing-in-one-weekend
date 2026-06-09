#ifndef SCENE__RTTNW__SCENE4_HPP
#define SCENE__RTTNW__SCENE4_HPP

#include "../Scene.hpp"

#include <Camera/LensCamera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Geometry/collection/BVH.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/Geometry.hpp>
#include <Material/Dielectric.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Material.hpp>
#include <Material/Metal.hpp>
#include <Renderer/RendererSkyBackground.hpp>
#include <Texture/CheckerBoardTexture.hpp>
#include <Texture/ImageTexture.hpp>

namespace RTTNW {

class Scene4 : public Scene {
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
        pinhole_camera->eye = vec4(0.0f, 0.0f, 12.0f);
        pinhole_camera->direction = vec4(0.0f, 0.0f, -12.0f);
        pinhole_camera->vfov = 1.0f / 9.0f * M_PI;
        pinhole_camera->setup(framebuffer);
        camera = pinhole_camera;
    }

    void init_world() override {
        // Scene PRNG
        PRNG prng = PRNG(PRNG_SEED);

        // Setup scene
        std::shared_ptr<Texture> earth_tex = std::make_shared<ImageTexture>("../img/earthmap.jpg");
        std::shared_ptr<Material> earth_mat = std::make_shared<Lambertian>(earth_tex);
        world = std::make_shared<Sphere>(vec4(0.0f, 0.0f, 0.0f), 2.0f, earth_mat);
    }
};

}

#endif