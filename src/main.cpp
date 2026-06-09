#include <io/FramebufferExport.hpp>
#include <Camera/Camera.hpp>
#include <Geometry/Geometry.hpp>
#include <Renderer/Renderer.hpp>
#include <Framebuffer.hpp>
#include <PostProcessing.hpp>
#include <memory>

#include <../scene/rtiow_scene_l.hpp>
#include <../scene/rttnw_scene_l.hpp>

int main() {

    // Setup scene
    Framebuffer framebuffer;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Geometry> world;
    rttnw_scene10(renderer, framebuffer, camera, world);

    // Render
    renderer->render(framebuffer, camera, world);
    PostProcessing::gamma(framebuffer, 1.0f / 2.2f);

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}