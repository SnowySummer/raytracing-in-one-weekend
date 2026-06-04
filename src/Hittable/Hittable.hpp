#ifndef HITTABLE__HITTABLE_HPP
#define HITTABLE__HITTABLE_HPP

#include <Interval.hpp>
#include <Ray.hpp>
#include <HitRecord.hpp>

class Hittable {
public:
    // Hittable virtual destructor
    virtual ~Hittable() {}

    // Ray intersection
    virtual bool ray_hit(Ray ray, Interval interval, HitRecord& record) const = 0;
};

#endif