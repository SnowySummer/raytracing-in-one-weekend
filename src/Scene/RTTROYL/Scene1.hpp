#ifndef SCENE__RTTROYL__SCENE1_HPP
#define SCENE__RTTROYL__SCENE1_HPP

#include "../Scene.hpp"

#include <Camera/LensCamera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Geometry/collection/Box.hpp>
#include <Geometry/collection/BVH.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Quad.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/transform/RotateY.hpp>
#include <Geometry/transform/Translate.hpp>
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

namespace RTTROYL {

class Scene1 : public Scene {
public:
    static constexpr uint32_t PRNG_SEED = 1337;

public:
    void init_framebuffer() override {
        framebuffer = Framebuffer(400, 400);
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
        pinhole_camera->eye = vec4(278.0f, 278.0f, -800.0f);
        pinhole_camera->direction = vec4(0.0f, 0.0f, 800.0f);
        pinhole_camera->vfov = 2.0f / 9.0f * M_PI;
        pinhole_camera->setup(framebuffer);
        camera = pinhole_camera;
    }

    void init_world() override {
        // Scene PRNG
        PRNG prng = PRNG(PRNG_SEED);

        // Setup scene
        std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

        std::shared_ptr<Material> red   = std::make_shared<Lambertian>(vec4(0.65f, 0.05f, 0.05f));
        std::shared_ptr<Material> white = std::make_shared<Lambertian>(vec4(0.73f, 0.73f, 0.73f));
        std::shared_ptr<Material> green = std::make_shared<Lambertian>(vec4(0.12f, 0.45f, 0.15f));
        std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(vec4(15.0f, 15.0f, 15.0f));

        geometry_l->add(std::make_shared<Quad>(vec4(555.0f,   0.0f,   0.0f), vec4(   0.0f, 555.0f, 0.0f), vec4(0.0f,   0.0f,  555.0f), green));
        geometry_l->add(std::make_shared<Quad>(vec4(  0.0f,   0.0f,   0.0f), vec4(   0.0f, 555.0f, 0.0f), vec4(0.0f,   0.0f,  555.0f), red));
        geometry_l->add(std::make_shared<Quad>(vec4(343.0f, 554.0f, 332.0f), vec4(-130.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f, -105.0f), light));
        geometry_l->add(std::make_shared<Quad>(vec4(  0.0f,   0.0f,   0.0f), vec4( 555.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f,  555.0f), white));
        geometry_l->add(std::make_shared<Quad>(vec4(555.0f, 555.0f, 555.0f), vec4(-555.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f, -555.0f), white));
        geometry_l->add(std::make_shared<Quad>(vec4(  0.0f,   0.0f, 555.0f), vec4( 555.0f,   0.0f, 0.0f), vec4(0.0f, 555.0f,    0.0f), white));

        std::shared_ptr<Geometry> box1 = Box(vec4(0.0f, 0.0f, 0.0f), vec4(165.0f, 330.0f, 165.0f), white);
        box1 = std::make_shared<RotateY>(box1, 1.0f / 12.0f * M_PI);
        box1 = std::make_shared<Translate>(box1, vec4(265.0f, 0.0f, 295.0f));
        
        std::shared_ptr<Geometry> box2 = Box(vec4(0.0f, 0.0f, 0.0f), vec4(165.0f, 165.0f, 165.0f), white);
        box2 = std::make_shared<RotateY>(box2, -1.0f / 10.0f * M_PI);
        box2 = std::make_shared<Translate>(box2, vec4(130.0f, 0.0f, 65.0f));
        
        geometry_l->add(box1);
        geometry_l->add(box2);
        
        world = geometry_l;
    }
    

    void init_light_hint() override {
        use_light = true;
        std::shared_ptr<GeometryList> light_hint_l = std::make_shared<GeometryList>();
        
        light_hint_l->add(std::make_shared<Quad>(vec4(343.0f, 554.0f, 332.0f), vec4(-130.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f, -105.0f), nullptr));

        light_hint = light_hint_l;
    }
};

}

#endif