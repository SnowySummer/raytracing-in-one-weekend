#include <Framebuffer.hpp>
#include <Camera.hpp>
#include <Renderer.hpp>
#include <io/FramebufferExport.hpp>

int main() {

    // Setup framebuffer
    Framebuffer framebuffer = Framebuffer(400, 225);

    // Setup camera
    Camera camera;
    camera.setup(framebuffer);

    // Render
    Renderer renderer;
    renderer.render(framebuffer, camera);

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}