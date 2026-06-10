#ifndef MATERIAL__DIELECTRIC_HPP
#define MATERIAL__DIELECTRIC_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>

class Dielectric : public Material {
public:
    float refraction_index;

public:
    // Dielectric constructor
    Dielectric() : refraction_index(1.0f) {}
    Dielectric(float _refraction_index) : refraction_index(_refraction_index) {}
    
    // Light emission
    vec4 light_emission(Ray ray, HitRecord record, float u, float v, vec4 p) override {
        return vec4(0.0f, 0.0f, 0.0f);
    }

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        // Set attenuation
        srec.attenuation = vec4(1.0f, 1.0f, 1.0f);

        // Select ray to be scattered
        float ri = record.front_face ? 1.0f / refraction_index : refraction_index;
        float cos_theta = vec4::dot(-ray.direction, record.n);
        float sin_theta = std::sqrt(1.0f - cos_theta*cos_theta);
        
        srec.skip_pdf = true;
        srec.scatter_ray.origin = record.p;
        srec.scatter_ray.time = ray.time;
        if (1 < ri * sin_theta || prng.randf() < reflectance(cos_theta, ri)) {
            srec.scatter_ray.direction = vec4::normalise(vec4::reflect(ray.direction, record.n));
        } else {
            srec.scatter_ray.direction = vec4::normalise(vec4::refract(ray.direction, record.n, ri));
        }
        return true;
    }
    float scatter_pdf(Ray ray, HitRecord record, Ray scatter_ray) override {
        return 0.0f;
    }

private:
    // Schlick approximation for reflectance
    static float reflectance(float cos_theta, float ri) {
        float r0 = (1.0f - ri) / (1.0f + ri);
        r0 = r0*r0;
        return r0 + (1.0f - r0) * std::pow(1.0f - cos_theta, 5);
    }
};

#endif