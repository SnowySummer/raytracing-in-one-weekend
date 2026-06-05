#ifndef MATERIAL__DIELECTRIC_HPP
#define MATERIAL__DIELECTRIC_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>

class Dielectric : public Material {
public:
    float refraction_index;

public:
    // Lambertian constructor
    Dielectric() : refraction_index(1.0f) {}
    Dielectric(float _refraction_index) : refraction_index(_refraction_index) {}

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        srec.attenuation = vec4(1.0f, 1.0f, 1.0f);

        float ri = record.front_face ? 1.0f / refraction_index : refraction_index;

        float cos_theta = vec4::dot(-ray.direction, record.n);
        float sin_theta = std::sqrt(1.0f - cos_theta*cos_theta);
        if (sin_theta * ri < 1 && reflectance(cos_theta, ri) < prng.randf()) {
            // Refract ray
            vec4 scatter_direction = vec4::normalise(vec4::refract(ray.direction, record.n, ri));
            srec.scatter_ray = Ray(record.p, scatter_direction);
        } else {
            // Reflect ray
            vec4 scatter_direction = vec4::normalise(vec4::reflect(ray.direction, record.n));
            srec.scatter_ray = Ray(record.p, scatter_direction);
        }
        return true;
    }

private:
    static float reflectance(float cos_theta, float ri) {
        float r0 = (1.0f - ri) / (1.0f + ri);
        r0 = r0*r0;
        return r0 + (1.0f - r0) * std::pow(1.0f - cos_theta, 5);
    }
};

#endif