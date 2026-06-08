#ifndef GEOMETRY__PRIMITIVE__CONSTANTMEDIUM_HPP
#define GEOMETRY__PRIMITIVE__CONSTANTMEDIUM_HPP

#include "../Geometry.hpp"

#include <Material/Isotropic.hpp>

class ConstantMedium : public Geometry {
public:
    std::shared_ptr<Geometry> boundary;
    float density;
    std::shared_ptr<Material> phase_function;

public:
    // ConstantMedium constructor
    ConstantMedium() {}
    ConstantMedium(std::shared_ptr<Geometry> _boundary, float _density, vec4 color) :
    boundary(_boundary),
    density(_density),
    phase_function(std::make_shared<Isotropic>(color)) {}

    // Ray intersection
    bool ray_hit(PRNG& prng, Ray ray, Interval interval, HitRecord& record) const override {
        // Get boundary
        HitRecord record1;
        HitRecord record2;

        if (!boundary->ray_hit(prng, ray, Interval(-INFINITY, INFINITY), record1)) return false;
        if (!boundary->ray_hit(prng, ray, Interval(record1.t + 1e-4f, INFINITY), record2)) return false;

        // Check boundary interval
        if (record1.t < interval.min) record1.t = interval.min;
        if (interval.max < record2.t) record2.t = interval.max;
        if (record1.t < 0) record1.t = 0;

        if (record2.t <= record1.t) return false;

        // Fetch scatter point
        float in_boundary_dist = (record2.t - record1.t) * ray.direction.len();
        float hit_distance = -std::log(prng.randf()) / density;

        if (in_boundary_dist < hit_distance) return false;

        // Update record
        record.t = record1.t + hit_distance / ray.direction.len();
        record.p = ray.at(record.t);
        record.n = vec4(1.0f, 0.0f, 0.0f);
        record.u = 0.0f;
        record.v = 0.0f;
        record.front_face = true;
        record.mat = phase_function;
        return true;
    }
};

#endif