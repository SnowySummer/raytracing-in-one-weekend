#ifndef MATERIAL__LAMBERTIAN_HPP
#define MATERIAL__LAMBERTIAN_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>

class Lambertian : public Material {
public:
    vec4 albedo;

public:
    // Lambertian constructor
    Lambertian() : albedo(vec4()) {}
    Lambertian(vec4 _albedo) : albedo(_albedo) {}

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        srec.attenuation = albedo;
        srec.scatter_ray = Ray(record.p, vec4::normalise(record.n + prng.on_sphere()));
        return true;
    }
};

#endif