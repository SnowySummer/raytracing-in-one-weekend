#ifndef GEOMETRY__GEOMETRY_HPP
#define GEOMETRY__GEOMETRY_HPP

#include <common/Interval.hpp>
#include <common/PRNG.hpp>
#include <common/Ray.hpp>
#include <HitRecord.hpp>
#include <BBox.hpp>

class Geometry {
public:
    BBox bbox;

public:
    // Geometry virtual destructor
    virtual ~Geometry() {}

    // Ray intersection
    virtual bool ray_hit(PRNG& prng, Ray ray, Interval interval, HitRecord& record) const = 0;
};

#endif