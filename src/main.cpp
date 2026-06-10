#include <io/FramebufferExport.hpp>
#include <Camera/Camera.hpp>
#include <Geometry/Geometry.hpp>
#include <Renderer/Renderer.hpp>
#include <Framebuffer.hpp>
#include <PostProcessing.hpp>
#include <memory>

// RTIOW scenes
#include <Scene/RTIOW/Scene1.hpp>
#include <Scene/RTIOW/Scene2.hpp>
#include <Scene/RTIOW/Scene3.hpp>
#include <Scene/RTIOW/Scene4.hpp>
#include <Scene/RTIOW/Scene5.hpp>

// RTTNW scenes
#include <Scene/RTTNW/Scene1.hpp>
#include <Scene/RTTNW/Scene2.hpp>
#include <Scene/RTTNW/Scene3.hpp>
#include <Scene/RTTNW/Scene4.hpp>
#include <Scene/RTTNW/Scene5.hpp>
#include <Scene/RTTNW/Scene6.hpp>
#include <Scene/RTTNW/Scene7.hpp>
#include <Scene/RTTNW/Scene8.hpp>
#include <Scene/RTTNW/Scene9.hpp>
#include <Scene/RTTNW/Scene10.hpp>

// RTTROYL scenes
#include <Scene/RTTROYL/Scene1.hpp>
#include <Scene/RTTROYL/Scene2.hpp>
#include <Scene/RTTROYL/Scene3.hpp>

int main() {

    // Setup scene and render
    std::shared_ptr<Scene> scene = std::make_shared<RTTNW::Scene9>();
    scene->init_all();
    scene->render();

    // Export to PNG
    FramebufferExport::to_png(scene->framebuffer, "../gen/img.png");

    return 0;
}