#ifndef SCENE__RTTNW__SCENE7_HPP
#define SCENE__RTTNW__SCENE7_HPP

#include "../Scene.hpp"

#include <Camera/LensCamera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Geometry/collection/BVH.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Quad.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/Geometry.hpp>
#include <Material/Dielectric.hpp>
#include <Material/DiffuseLight.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Material.hpp>
#include <Material/Metal.hpp>
#include <Renderer/RendererSkyBackground.hpp>
#include <Renderer/RendererSolidBackground.hpp>
#include <Texture/CheckerBoardTexture.hpp>
#include <Texture/ImageTexture.hpp>
#include <Texture/NoiseTexture.hpp>

namespace RTTNW {

class Scene7 : public Scene {
public:
    static constexpr uint32_t PRNG_SEED = 1337;

public:
    void init_framebuffer() override {
        framebuffer = Framebuffer(400, 225);
    }

    void init_renderer() override {
        renderer = std::make_shared<RendererSolidBackground>();
        renderer->prng.set_seed(PRNG_SEED);
        renderer->samples_per_pixel = 100;
        renderer->ray_maxdepth = 10;
    }

    void init_camera() override {
        std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
        pinhole_camera->prng.set_seed(PRNG_SEED);
        pinhole_camera->eye = vec4(26.0f, 3.0f, 6.0f);
        pinhole_camera->direction = vec4(-26.0f, -1.0f, -6.0f);
        pinhole_camera->vfov = 1.0f / 9.0f * M_PI;
        pinhole_camera->setup(framebuffer);
        camera = pinhole_camera;
    }

    void init_world() override {
        // Scene PRNG
        PRNG prng = PRNG(PRNG_SEED);

        // Setup scene
        std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

        std::shared_ptr<Texture> perlin_tex = std::make_shared<NoiseTexture>(prng, 4);
        std::shared_ptr<Material> perlin_mat = std::make_shared<Lambertian>(perlin_tex);
        geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, 0.0f), 1000.0f, perlin_mat));
        geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, 2.0f, 0.0f), 2.0f, perlin_mat));
        
        std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(vec4(4.0f, 4.0f, 4.0f));
        geometry_l->add(std::make_shared<Quad>(vec4(3.0f, 1.0f, -2.0f), vec4(2.0f, 0.0f, 0.0f), vec4(0.0f, 2.0f, 0.0f), light));
        
        world = geometry_l;
    }

    void init_light_hint() override {
        use_light = false;
    }
};

}

#endif