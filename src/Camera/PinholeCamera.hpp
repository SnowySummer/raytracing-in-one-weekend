#ifndef CAMERA__PINHOLECAMERA_HPP
#define CAMERA__PINHOLECAMERA_HPP

#include "Camera.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <Framebuffer.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

class PinholeCamera : public Camera {
public:
    PRNG prng;
    vec4 eye;
    vec4 direction;
    vec4 up;
    float vfov;
    float viewport_distance;

private:
    vec4 viewport_origin;
    vec4 viewport_right;
    vec4 viewport_up;

public:
    // PinholeCamera constructor
    PinholeCamera() :
    prng(),
    eye(vec4(0.0f, 0.0f, 0.0f)),
    direction(vec4(0.0f, 0.0f, -1.0f)),
    up(vec4(0.0f, 1.0f, 0.0f)),
    vfov(0.5f * M_PI),
    viewport_distance(1.0f),
    viewport_origin(vec4()),
    viewport_right(vec4()),
    viewport_up(vec4()) {}

    // Setup camera
    void setup(const Framebuffer& framebuffer) {
        // Normalise vectors
        direction = vec4::normalise(direction);
        up = vec4::normalise(up);

        // Make orthonormal base
        viewport_right = vec4::normalise(vec4::cross(direction, up));
        viewport_up    = vec4::cross(viewport_right, direction);

        // Rescale to base to viewport dimensions
        viewport_up    *= viewport_distance * std::tanf(0.5f * vfov);
        viewport_right *= viewport_distance * std::tanf(0.5f * vfov) * float(framebuffer.width) / float(framebuffer.height);

        // Move origin to upper-left
        viewport_origin = eye + viewport_distance * direction;
        viewport_origin += viewport_up - viewport_right;

        // Rescale base to viewport-pixel dimensions
        viewport_right *= 2.0f / float(framebuffer.width);
        viewport_up    *= 2.0f / float(framebuffer.height);

        // Move viewport origin to pixel center
        viewport_origin +=  0.5f * viewport_right;
        viewport_origin += -0.5f * viewport_up;
    }

    // Generate ray
    Ray gen_ray(float x, float y) override {
        // Ray points
        vec4 ray_origin = eye;
        vec4 ray_viewport = viewport_origin + x * viewport_right - y * viewport_up;

        // Jitter camera
        vec4 pixel_offset = 0.5f * prng.square();
        ray_viewport += pixel_offset[0]*viewport_right + pixel_offset[1]*viewport_up;

        return Ray(ray_origin, vec4::normalise(ray_viewport - ray_origin));
    }
};


#endif