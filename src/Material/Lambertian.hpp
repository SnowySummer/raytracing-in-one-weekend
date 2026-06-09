#ifndef MATERIAL__LAMBERTIAN_HPP
#define MATERIAL__LAMBERTIAN_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>
#include <PDF/CosinePDF.hpp>
#include <Texture/SolidColorTexture.hpp>
#include <Texture/Texture.hpp>

#include <memory>

class Lambertian : public Material {
public:
    std::shared_ptr<Texture> tex;

public:
    // Lambertian constructor
    Lambertian() : tex(nullptr) {}
    Lambertian(vec4 albedo) : tex(std::make_shared<SolidColorTexture>(albedo)) {}
    Lambertian(std::shared_ptr<Texture> _tex) : tex(_tex) {}

    // Light emission
    vec4 light_emission(float u, float v, vec4 p) override {
        return vec4(0.0f, 0.0f, 0.0f);
    }
    
    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        srec.attenuation = tex->value(record.u, record.v, record.p);
        srec.skip_pdf = false;
        srec.pdf = std::make_shared<CosinePDF>(record.n);
        return true;
    }
    float scatter_pdf(Ray ray, HitRecord record, Ray scatter_ray) override {
        float cos_theta = vec4::dot(record.n, vec4::normalise(scatter_ray.direction));
        return (cos_theta < 0) ? 0.0f : cos_theta / M_PI;
    }
};

#endif