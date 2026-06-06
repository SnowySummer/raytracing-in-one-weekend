#ifndef HITTABLE__HITTABLE_HPP
#define HITTABLE__HITTABLE_HPP

#include <common/Interval.hpp>
#include <common/Ray.hpp>
#include <HitRecord.hpp>
#include <BBox.hpp>

class Hittable {
public:
    BBox bbox;

public:
    // Hittable virtual destructor
    virtual ~Hittable() {}

    // Ray intersection
    virtual bool ray_hit(Ray ray, Interval interval, HitRecord& record) const = 0;
};

#endif