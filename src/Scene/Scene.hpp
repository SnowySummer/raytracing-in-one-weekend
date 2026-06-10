#ifndef SCENE__SCENE_HPP
#define SCENE__SCENE_HPP

#include <Camera/Camera.hpp>
#include <Geometry/Geometry.hpp>
#include <Renderer/Renderer.hpp>
#include <Framebuffer.hpp>
#include <PostProcessing.hpp>
#include <memory>

class Scene {
public:
    Framebuffer framebuffer;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Camera>   camera;
    std::shared_ptr<Geometry> world;
    bool use_light;
    std::shared_ptr<Geometry> light_hint;

public:
    // Scene virtual destructor
    virtual ~Scene() {}

    // Initialise each component
    void init_all() {
        init_framebuffer();
        init_renderer();
        init_camera();
        init_world();
        init_light_hint();
    }
    
    virtual void init_framebuffer() = 0;
    virtual void init_renderer() = 0;
    virtual void init_camera() = 0;
    virtual void init_world() = 0;
    virtual void init_light_hint() = 0;

    // Render
    void render() {
        renderer->render(framebuffer, camera, world, use_light, light_hint);
        PostProcessing::gamma(framebuffer, 1.0f / 2.2f);
    }
};

#endif