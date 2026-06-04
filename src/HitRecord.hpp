#ifndef HITRECORD_HPP
#define HITRECORD_HPP

#include <common/vec4.hpp>
#include <common/Ray.hpp>

class HitRecord {
public:
    float t;
    vec4 p;
    vec4 n;
    bool front_face;

public:
    // Automatic set front face
    void set_front_face(Ray ray, vec4 normal) {
        front_face = vec4::dot(ray.direction, normal) < 0;
        n = (front_face) ? normal : -normal;
    }
};

#endif