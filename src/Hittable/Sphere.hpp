#ifndef HITTABLE__SPHERE_HPP
#define HITTABLE__SPHERE_HPP

#include "Hittable.hpp"

#include <Interval.hpp>
#include <vec4.hpp>
#include <Ray.hpp>
#include <HitRecord.hpp>

class Sphere : public Hittable {
public:
    vec4 center;
    float radius;

public:
    // Sphere constructor
    Sphere() : center(vec4(0.0f, 0.0f, 0.0f)), radius(1.0f) {}
    Sphere(vec4 _center, float _radius) : center(_center), radius(_radius) {}

    // Ray intersection
    bool ray_hit(Ray ray, Interval interval, HitRecord& record) const override {
        // Check line intersection
        float a = ray.direction.len2();
        float b = vec4::dot(ray.origin - center, ray.direction);
        float c = (ray.origin - center).len2() - radius*radius;
        if (b*b - a*c < 0) return false;

        // Check in interval
        float discr = std::sqrt(b*b - a*c);
        float t = (-b - discr) / a;
        if (!interval.contains(t)) {
            t = (-b + discr) / a;
            if (!interval.contains(t)) return false;
        }

        // Update record
        record.t = t;
        record.p = ray.at(t);
        record.n = (record.p - center) / radius;

        return true;
    }
};

#endif