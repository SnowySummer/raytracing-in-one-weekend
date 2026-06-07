#ifndef MATERIAL__METAL_HPP
#define MATERIAL__METAL_HPP

#include "Material.hpp"

#include <common/PRNG.hpp>
#include <common/vec4.hpp>

class Metal : public Material {
public:
    std::shared_ptr<Texture> tex;
    float fuzz;

public:
    // Metal constructor
    Metal() : tex(nullptr) {}
    Metal(vec4 albedo) : tex(std::make_shared<SolidColorTexture>(albedo)), fuzz(0.0f) {}
    Metal(vec4 albedo, float _fuzz) : tex(std::make_shared<SolidColorTexture>(albedo)), fuzz(_fuzz) {}
    Metal(std::shared_ptr<Texture> _tex, float _fuzz) : tex(_tex), fuzz(_fuzz) {}

    // Light emission
    vec4 light_emission(float u, float v, vec4 p) override {
        return vec4(0.0f, 0.0f, 0.0f);
    }

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        srec.attenuation = tex->value(record.u, record.v, record.p);
        vec4 scatter_direction = vec4::normalise(vec4::reflect(ray.direction, record.n) + fuzz * prng.on_sphere());
        srec.scatter_ray = Ray(record.p, scatter_direction, ray.time);
        return true;
    }
};

#endif