#ifndef MATERIAL__METAL_HPP
#define MATERIAL__METAL_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>

class Metal : public Material {
public:
    vec4 albedo;
    float fuzz;

public:
    // Metal constructor
    Metal() : albedo(vec4()) {}
    Metal(vec4 _albedo) : albedo(_albedo), fuzz(0.0f) {}
    Metal(vec4 _albedo, float _fuzz) : albedo(_albedo), fuzz(_fuzz) {}

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        srec.attenuation = albedo;
        vec4 scatter_direction = vec4::normalise(vec4::reflect(ray.direction, record.n) + fuzz * prng.on_sphere());
        srec.scatter_ray = Ray(record.p, scatter_direction);
        return true;
    }
};

#endif