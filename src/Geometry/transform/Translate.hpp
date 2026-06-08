#ifndef GEOMETRY__TRANSFORM__TRANSLATE_HPP
#define GEOMETRY__TRANSFORM__TRANSLATE_HPP

#include "../Geometry.hpp"

#include <common/vec4.hpp>
#include <memory>

class Translate : public Geometry {
public:
    std::shared_ptr<Geometry> geometry;
    vec4 offset;

public:
    // Translate constructor
    Translate() : geometry(nullptr), offset(vec4(0.0f, 0.0f, 0.0f)) {}
    Translate(std::shared_ptr<Geometry> _geometry, vec4 _offset) : geometry(_geometry), offset(_offset) {
        bbox = geometry->bbox + offset;
    }

    // Ray intersection
    bool ray_hit(Ray ray, Interval interval, HitRecord& record) const override {
        // Offset ray
        Ray offset_ray = Ray(ray.origin - offset, ray.direction, ray.time);

        // Check intersection
        if (!geometry->ray_hit(offset_ray, interval, record)) return false;

        // Offset record value
        record.p += offset;
        return true;
    }
};

#endif