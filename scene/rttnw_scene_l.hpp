#ifndef SCENE__RTTNW_SCENE_L_HPP
#define SCENE__RTTNW_SCENE_L_HPP

#include <Framebuffer.hpp>
#include <Renderer/Renderer.hpp>
#include <Renderer/RendererSkyBackground.hpp>
#include <Renderer/RendererSolidBackground.hpp>
#include <Camera/Camera.hpp>
#include <Camera/PinholeCamera.hpp>
#include <Camera/LensCamera.hpp>
#include <Material/Material.hpp>
#include <Material/DiffuseLight.hpp>
#include <Material/Lambertian.hpp>
#include <Material/Metal.hpp>
#include <Material/Dielectric.hpp>
#include <Geometry/Geometry.hpp>
#include <Geometry/collection/Box.hpp>
#include <Geometry/collection/BVH.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/ConstantMedium.hpp>
#include <Geometry/primitive/Quad.hpp>
#include <Geometry/primitive/Sphere.hpp>
#include <Geometry/transform/RotateY.hpp>
#include <Geometry/transform/Translate.hpp>
#include <Texture/Texture.hpp>
#include <Texture/CheckerBoardTexture.hpp>
#include <Texture/ImageTexture.hpp>
#include <Texture/NoiseTexture.hpp>
#include <memory>

void rttnw_scene1(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<LensCamera> lens_camera = std::make_shared<LensCamera>();
    lens_camera->prng.set_seed(prng_seed);
    lens_camera->eye = vec4(13.0f, 2.0f, 3.0f);
    lens_camera->direction = vec4(-13.0f, -2.0f, -3.0f);
    lens_camera->vfov = 1.0f / 9.0f * M_PI;
    lens_camera->defocus_angle = 1.0f / 300.0f * M_PI;
    lens_camera->focal_distance = 10.0f;
    lens_camera->setup(framebuffer);
    camera = lens_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.5f, 0.5f, 0.5f));
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, -1.0f), 1000.0f, ground_mat));

    std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(vec4(0.4f, 0.2f, 0.1f));
    std::shared_ptr<Material> material3 = std::make_shared<Metal>(vec4(0.7f, 0.6f, 0.5f));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, 1.0f, 0.0f), 1.0f, material1));
    geometry_l->add(std::make_shared<Sphere>(vec4(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    geometry_l->add(std::make_shared<Sphere>(vec4( 4.0f, 1.0f, 0.0f), 1.0f, material3));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            // Choose sphere center
            vec4 sphere_center1 = vec4(a + 0.9f*prng.randf(), 0.2f, b + 0.9f * prng.randf());
            if ((sphere_center1 - vec4(4.0f, 0.2f, 0.0f)).len() < 0.9f) continue;
            vec4 sphere_center2 = sphere_center1;

            // Choose sphere material
            float choose_mat = prng.randf();
            std::shared_ptr<Material> sphere_mat;
            if (choose_mat < 0.8f) {
                vec4 albedo = prng.color() * prng.color();
                sphere_mat = std::make_shared<Lambertian>(albedo);

                sphere_center2 = sphere_center1 + vec4(0.0f, prng.randf(0.0f, 0.5f), 0.0f);
            } else if (choose_mat < 0.9f) {
                vec4 albedo = 0.5f * (vec4(1.0f, 1.0f, 1.0f) + prng.color());
                float fuzz = 0.5f * prng.randf();
                sphere_mat = std::make_shared<Metal>(albedo, fuzz);
            } else {
                sphere_mat = std::make_shared<Dielectric>(1.5f);
            }

            // Add sphere
            geometry_l->add(std::make_shared<Sphere>(sphere_center1, sphere_center2, 0.2f, sphere_mat));
        }
    }

    world = geometry_l;
}

void rttnw_scene2(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<LensCamera> lens_camera = std::make_shared<LensCamera>();
    lens_camera->prng.set_seed(prng_seed);
    lens_camera->eye = vec4(13.0f, 2.0f, 3.0f);
    lens_camera->direction = vec4(-13.0f, -2.0f, -3.0f);
    lens_camera->vfov = 1.0f / 9.0f * M_PI;
    lens_camera->defocus_angle = 1.0f / 300.0f * M_PI;
    lens_camera->focal_distance = 10.0f;
    lens_camera->setup(framebuffer);
    camera = lens_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(vec4(0.5f, 0.5f, 0.5f));
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, -1.0f), 1000.0f, ground_mat));

    std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(vec4(0.4f, 0.2f, 0.1f));
    std::shared_ptr<Material> material3 = std::make_shared<Metal>(vec4(0.7f, 0.6f, 0.5f));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, 1.0f, 0.0f), 1.0f, material1));
    geometry_l->add(std::make_shared<Sphere>(vec4(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    geometry_l->add(std::make_shared<Sphere>(vec4( 4.0f, 1.0f, 0.0f), 1.0f, material3));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            // Choose sphere center
            vec4 sphere_center1 = vec4(a + 0.9f*prng.randf(), 0.2f, b + 0.9f * prng.randf());
            if ((sphere_center1 - vec4(4.0f, 0.2f, 0.0f)).len() < 0.9f) continue;
            vec4 sphere_center2 = sphere_center1;

            // Choose sphere material
            float choose_mat = prng.randf();
            std::shared_ptr<Material> sphere_mat;
            if (choose_mat < 0.8f) {
                vec4 albedo = prng.color() * prng.color();
                sphere_mat = std::make_shared<Lambertian>(albedo);

                sphere_center2 = sphere_center1 + vec4(0.0f, prng.randf(0.0f, 0.5f), 0.0f);
            } else if (choose_mat < 0.9f) {
                vec4 albedo = 0.5f * (vec4(1.0f, 1.0f, 1.0f) + prng.color());
                float fuzz = 0.5f * prng.randf();
                sphere_mat = std::make_shared<Metal>(albedo, fuzz);
            } else {
                sphere_mat = std::make_shared<Dielectric>(1.5f);
            }

            // Add sphere
            geometry_l->add(std::make_shared<Sphere>(sphere_center1, sphere_center2, 0.2f, sphere_mat));
        }
    }

    std::shared_ptr<BVH> world_bvh = std::make_shared<BVH>(geometry_l);

    world = world_bvh;
}

void rttnw_scene3(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<LensCamera> lens_camera = std::make_shared<LensCamera>();
    lens_camera->prng.set_seed(prng_seed);
    lens_camera->eye = vec4(13.0f, 2.0f, 3.0f);
    lens_camera->direction = vec4(-13.0f, -2.0f, -3.0f);
    lens_camera->vfov = 1.0f / 9.0f * M_PI;
    lens_camera->defocus_angle = 1.0f / 300.0f * M_PI;
    lens_camera->focal_distance = 10.0f;
    lens_camera->setup(framebuffer);
    camera = lens_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    std::shared_ptr<Texture> ground_tex = std::make_shared<CheckerBoardTexture>(0.32, vec4(0.2f, 0.3f, 0.1f), vec4(0.9f, 0.9f, 0.9f));
    std::shared_ptr<Material> ground_mat = std::make_shared<Lambertian>(ground_tex);
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, -1.0f), 1000.0f, ground_mat));

    std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
    std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(vec4(0.4f, 0.2f, 0.1f));
    std::shared_ptr<Material> material3 = std::make_shared<Metal>(vec4(0.7f, 0.6f, 0.5f));
    geometry_l->add(std::make_shared<Sphere>(vec4( 0.0f, 1.0f, 0.0f), 1.0f, material1));
    geometry_l->add(std::make_shared<Sphere>(vec4(-4.0f, 1.0f, 0.0f), 1.0f, material2));
    geometry_l->add(std::make_shared<Sphere>(vec4( 4.0f, 1.0f, 0.0f), 1.0f, material3));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            // Choose sphere center
            vec4 sphere_center1 = vec4(a + 0.9f*prng.randf(), 0.2f, b + 0.9f * prng.randf());
            if ((sphere_center1 - vec4(4.0f, 0.2f, 0.0f)).len() < 0.9f) continue;
            vec4 sphere_center2 = sphere_center1;

            // Choose sphere material
            float choose_mat = prng.randf();
            std::shared_ptr<Material> sphere_mat;
            if (choose_mat < 0.8f) {
                vec4 albedo = prng.color() * prng.color();
                sphere_mat = std::make_shared<Lambertian>(albedo);

                sphere_center2 = sphere_center1 + vec4(0.0f, prng.randf(0.0f, 0.5f), 0.0f);
            } else if (choose_mat < 0.9f) {
                vec4 albedo = 0.5f * (vec4(1.0f, 1.0f, 1.0f) + prng.color());
                float fuzz = 0.5f * prng.randf();
                sphere_mat = std::make_shared<Metal>(albedo, fuzz);
            } else {
                sphere_mat = std::make_shared<Dielectric>(1.5f);
            }

            // Add sphere
            geometry_l->add(std::make_shared<Sphere>(sphere_center1, sphere_center2, 0.2f, sphere_mat));
        }
    }

    std::shared_ptr<BVH> world_bvh = std::make_shared<BVH>(geometry_l);

    world = world_bvh;
}

void rttnw_scene4(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(0.0f, 0.0f, 12.0f);
    pinhole_camera->direction = vec4(0.0f, 0.0f, -12.0f);
    pinhole_camera->vfov = 1.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<Texture> earth_tex = std::make_shared<ImageTexture>("../img/earthmap.jpg");
    std::shared_ptr<Material> earth_mat = std::make_shared<Lambertian>(earth_tex);
    world = std::make_shared<Sphere>(vec4(0.0f, 0.0f, 0.0f), 2.0f, earth_mat);
}

void rttnw_scene5(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(13.0f, 2.0f, 3.0f);
    pinhole_camera->direction = vec4(-13.0f, -2.0f, -3.0f);
    pinhole_camera->vfov = 1.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    PRNG noise_texture_prng = PRNG(prng_seed);
    std::shared_ptr<Texture> perlin_tex = std::make_shared<NoiseTexture>(prng, 4);
    std::shared_ptr<Material> perlin_mat = std::make_shared<Lambertian>(perlin_tex);
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, 0.0f), 1000.0f, perlin_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, 2.0f, 0.0f), 2.0f, perlin_mat));
    world = geometry_l;
}

void rttnw_scene6(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSkyBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 400);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(0.0f, 0.0f, 9.0f);
    pinhole_camera->direction = vec4(0.0f, 0.0f, -9.0f);
    pinhole_camera->vfov = 4.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    std::shared_ptr<Material> left_red     = std::make_shared<Lambertian>(vec4(1.0f, 0.2f, 0.2f));
    std::shared_ptr<Material> back_green   = std::make_shared<Lambertian>(vec4(0.2f, 1.0f, 0.2f));
    std::shared_ptr<Material> right_blue   = std::make_shared<Lambertian>(vec4(0.2f, 0.2f, 1.0f));
    std::shared_ptr<Material> upper_orange = std::make_shared<Lambertian>(vec4(1.0f, 0.5f, 0.0f));
    std::shared_ptr<Material> lower_teal   = std::make_shared<Lambertian>(vec4(0.2f, 0.8f, 0.8f));

    geometry_l->add(std::make_shared<Quad>(vec4(-3.0f, -2.0f, 5.0f), vec4(0.0f, 0.0f, -4.0f), vec4(0.0f, 4.0f,  0.0f), left_red));
    geometry_l->add(std::make_shared<Quad>(vec4(-2.0f, -2.0f, 0.0f), vec4(4.0f, 0.0f,  0.0f), vec4(0.0f, 4.0f,  0.0f), back_green));
    geometry_l->add(std::make_shared<Quad>(vec4( 3.0f, -2.0f, 1.0f), vec4(0.0f, 0.0f,  4.0f), vec4(0.0f, 4.0f,  0.0f), right_blue));
    geometry_l->add(std::make_shared<Quad>(vec4(-2.0f,  3.0f, 1.0f), vec4(4.0f, 0.0f,  0.0f), vec4(0.0f, 0.0f,  4.0f), upper_orange));
    geometry_l->add(std::make_shared<Quad>(vec4(-2.0f, -3.0f, 5.0f), vec4(4.0f, 0.0f,  0.0f), vec4(0.0f, 0.0f, -4.0f), lower_teal));
    world = geometry_l;
}

void rttnw_scene7(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSolidBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 225);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(26.0f, 3.0f, 6.0f);
    pinhole_camera->direction = vec4(-26.0f, -1.0f, -6.0f);
    pinhole_camera->vfov = 1.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    PRNG noise_texture_prng = PRNG(prng_seed);
    std::shared_ptr<Texture> perlin_tex = std::make_shared<NoiseTexture>(prng, 4);
    std::shared_ptr<Material> perlin_mat = std::make_shared<Lambertian>(perlin_tex);
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, -1000.0f, 0.0f), 1000.0f, perlin_mat));
    geometry_l->add(std::make_shared<Sphere>(vec4(0.0f, 2.0f, 0.0f), 2.0f, perlin_mat));
    
    std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(vec4(4.0f, 4.0f, 4.0f));
    geometry_l->add(std::make_shared<Quad>(vec4(3.0f, 1.0f, -2.0f), vec4(2.0f, 0.0f, 0.0f), vec4(0.0f, 2.0f, 0.0f), light));
    
    world = geometry_l;
}

void rttnw_scene8(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSolidBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 400);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(278.0f, 278.0f, -800.0f);
    pinhole_camera->direction = vec4(0.0f, 0.0f, 800.0f);
    pinhole_camera->vfov = 2.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

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

    world = geometry_l;
}

void rttnw_scene9(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSolidBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 400);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(278.0f, 278.0f, -800.0f);
    pinhole_camera->direction = vec4(0.0f, 0.0f, 800.0f);
    pinhole_camera->vfov = 2.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

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

void rttnw_scene10(
    std::shared_ptr<Renderer>& renderer,
    Framebuffer& framebuffer,
    std::shared_ptr<Camera>& camera,
    std::shared_ptr<Geometry>& world
) {
    // Setup main PRNG
    constexpr uint32_t prng_seed = 1337;
    PRNG prng = PRNG(prng_seed);

    // Setup renderer
    renderer = std::make_shared<RendererSolidBackground>();
    renderer->prng.set_seed(prng_seed);
    renderer->samples_per_pixel = 100;
    renderer->ray_maxdepth = 10;

    // Setup framebuffer
    framebuffer = Framebuffer(400, 400);

    // Setup camera
    std::shared_ptr<PinholeCamera> pinhole_camera = std::make_shared<PinholeCamera>();
    pinhole_camera->prng.set_seed(prng_seed);
    pinhole_camera->eye = vec4(278.0f, 278.0f, -800.0f);
    pinhole_camera->direction = vec4(0.0f, 0.0f, 800.0f);
    pinhole_camera->vfov = 2.0f / 9.0f * M_PI;
    pinhole_camera->setup(framebuffer);
    camera = pinhole_camera;

    // Setup scene
    std::shared_ptr<GeometryList> geometry_l = std::make_shared<GeometryList>();

    std::shared_ptr<Material> red   = std::make_shared<Lambertian>(vec4(0.65f, 0.05f, 0.05f));
    std::shared_ptr<Material> white = std::make_shared<Lambertian>(vec4(0.73f, 0.73f, 0.73f));
    std::shared_ptr<Material> green = std::make_shared<Lambertian>(vec4(0.12f, 0.45f, 0.15f));
    std::shared_ptr<Material> light = std::make_shared<DiffuseLight>(vec4(7.0f, 7.0f, 7.0f));

    geometry_l->add(std::make_shared<Quad>(vec4(555.0f,   0.0f,   0.0f), vec4(   0.0f, 555.0f, 0.0f), vec4(0.0f,   0.0f, 555.0f), green));
    geometry_l->add(std::make_shared<Quad>(vec4(  0.0f,   0.0f,   0.0f), vec4(   0.0f, 555.0f, 0.0f), vec4(0.0f,   0.0f, 555.0f), red));
    geometry_l->add(std::make_shared<Quad>(vec4(113.0f, 554.0f, 127.0f), vec4( 330.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f, 305.0f), light));
    geometry_l->add(std::make_shared<Quad>(vec4(  0.0f, 555.0f,   0.0f), vec4( 555.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f, 555.0f), white));
    geometry_l->add(std::make_shared<Quad>(vec4(  0.0f,   0.0f,   0.0f), vec4( 555.0f,   0.0f, 0.0f), vec4(0.0f,   0.0f, 555.0f), white));
    geometry_l->add(std::make_shared<Quad>(vec4(  0.0f,   0.0f, 555.0f), vec4( 555.0f,   0.0f, 0.0f), vec4(0.0f, 555.0f,   0.0f), white));

    std::shared_ptr<Geometry> box1 = Box(vec4(0.0f, 0.0f, 0.0f), vec4(165.0f, 330.0f, 165.0f), white);
    box1 = std::make_shared<RotateY>(box1, 1.0f / 12.0f * M_PI);
    box1 = std::make_shared<Translate>(box1, vec4(265.0f, 0.0f, 295.0f));
    
    std::shared_ptr<Geometry> box2 = Box(vec4(0.0f, 0.0f, 0.0f), vec4(165.0f, 165.0f, 165.0f), white);
    box2 = std::make_shared<RotateY>(box2, -1.0f / 10.0f * M_PI);
    box2 = std::make_shared<Translate>(box2, vec4(130.0f, 0.0f, 65.0f));
    
    geometry_l->add(std::make_shared<ConstantMedium>(box1, 0.01f, vec4(0.0f, 0.0f, 0.0f)));
    geometry_l->add(std::make_shared<ConstantMedium>(box2, 0.01f, vec4(1.0f, 1.0f, 1.0f)));
    
    world = geometry_l;
}


#endif