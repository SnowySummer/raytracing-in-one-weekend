#ifndef GEOMETRY__GEOMETRY_HPP
#define GEOMETRY__GEOMETRY_HPP

#include <common/Interval.hpp>
#include <common/PRNG.hpp>
#include <common/Ray.hpp>
#include <HitRecord.hpp>
#include <Geometry/BBox.hpp>

class Geometry {
public:
    BBox bbox;

public:
    // Geometry virtual destructor
    virtual ~Geometry() {}

    // Ray intersection
    virtual bool ray_hit(PRNG& prng, Ray ray, Interval interval, HitRecord& record) const = 0;

    // PDF functions
    virtual vec4 random(PRNG& prng, vec4 origin) {
        return vec4(1.0f, 0.0f, 0.0f);
    }
    virtual float pdf_value(PRNG& prng, vec4 origin, vec4 direction) {
        return 0.0f;
    }
};

#endif