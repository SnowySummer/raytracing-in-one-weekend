#ifndef MATERIAL__LAMBERTIAN_HPP
#define MATERIAL__LAMBERTIAN_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>
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

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        srec.attenuation = tex->value(record.u, record.v, record.p);
        srec.scatter_ray = Ray(record.p, vec4::normalise(record.n + prng.on_sphere()), ray.time);
        return true;
    }
};

#endif