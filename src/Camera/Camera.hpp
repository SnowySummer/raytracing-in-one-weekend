#ifndef CAMERA__CAMERA_HPP
#define CAMERA__CAMERA_HPP

#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <Framebuffer.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

class Camera {
public:
    // Camera virtual destructor
    virtual ~Camera() {}

    // Generate ray
    virtual Ray gen_ray(float x, float y) const = 0;
};


#endif