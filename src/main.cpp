#include <Framebuffer.hpp>
#include <Renderer/Renderer.hpp>
#include <Camera/Camera.hpp>
#include <Hittable/Hittable.hpp>
#include <PostProcessing.hpp>
#include <io/FramebufferExport.hpp>
#include <memory>
#include <string>

#include <../scene/rtiow_scene_l.hpp>
#include <../scene/rttnw_scene_l.hpp>

int main() {

    // Setup scene
    Framebuffer framebuffer;
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Hittable> world;
    rttnw_scene8(renderer, framebuffer, camera, world);

    // Render
    renderer->render(framebuffer, camera, world);
    PostProcessing::gamma(framebuffer, 1.0f / 2.2f);

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}