#include <Framebuffer.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Hittable/HittableList.hpp>
#include <Hittable/Sphere.hpp>
#include <Renderer.hpp>
#include <io/FramebufferExport.hpp>
#include <memory>

int main() {

    // Setup framebuffer
    Framebuffer framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<Camera> camera;
    std::shared_ptr<PinholeCamera> camera_impl = std::make_shared<PinholeCamera>();
    camera_impl->setup(framebuffer);
    camera = camera_impl;

    // Setup scene
    std::shared_ptr<Hittable> world;
    std::shared_ptr<HittableList> hittable_l = std::make_shared<HittableList>();
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, 0.0f, -1.0f), 0.5f));
    hittable_l->add(std::make_shared<Sphere>(vec4(0.0f, -100.5f, -1.0f), 100.0f));
    world = hittable_l;

    // Render
    Renderer renderer;
    renderer.render(framebuffer, camera, world);

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}