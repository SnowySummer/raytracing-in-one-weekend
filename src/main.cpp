#include <Framebuffer.hpp>
#include <FramebufferExport.hpp>

int main() {

    // Setup framebuffer
    Framebuffer framebuffer = Framebuffer(400, 225);
    framebuffer.clear(vec4(0.0f, 0.0f, 1.0f));

    // Export to PNG
    FramebufferExport::to_png(framebuffer, "../gen/img.png");

    return 0;
}