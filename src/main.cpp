#include <Framebuffer.hpp>
#include <Camera.hpp>
#include <FramebufferExport.hpp>

int main() {

    // Setup framebuffer
    Framebuffer framebuffer = Framebuffer(400, 225);

    // Setup camera
    Camera camera;
    camera.setup(framebuffer);

    // Render
    for (int y = 0; y < framebuffer.height; y++) {
        for (int x = 0; x < framebuffer.width; x++) {
            // Generate ray
            Ray ray = camera.gen_ray(x, y);
            float t = 0.5f * (1.0f + ray.direction[1]);
            framebuffer.get(x, y) = (1.0f - t) * vec4(1.0f, 1.0f, 1.0f) + t * vec4(0.5f, 0.7f, 1.0f);
        }
    }

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}