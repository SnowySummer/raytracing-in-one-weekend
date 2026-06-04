#include <Framebuffer.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Hittable/HittableList.hpp>
#include <Hittable/Sphere.hpp>
#include <Renderer.hpp>
#include <io/FramebufferExport.hpp>
#include <memory>

#include <../scene/rtiow_scene_l.hpp>

int main() {

    // Setup scene
    Framebuffer framebuffer;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Hittable> world;
    rtiow_scene1(framebuffer, camera, world);

    // Render
    Renderer renderer;
    renderer.render(framebuffer, camera, world);

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}