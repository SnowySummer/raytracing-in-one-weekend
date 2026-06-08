#ifndef MATERIAL__ISOTROPIC_HPP
#define MATERIAL__ISOTROPIC_HPP

#include "Material.hpp"

#include <Texture/SolidColorTexture.hpp>
#include <Texture/Texture.hpp>

class Isotropic : public Material {
public:
    std::shared_ptr<Texture> tex;

public:
    // Isotropic constructor
    Isotropic(): tex(nullptr) {}
    Isotropic(vec4 color): tex(std::make_shared<SolidColorTexture>(color)) {}
    Isotropic(std::shared_ptr<Texture> _tex): tex(_tex) {}

    // Light emission
    vec4 light_emission(float u, float v, vec4 p) override {
        return vec4(0.0f, 0.0f, 0.0f);
    }

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override{
        srec.attenuation = tex->value(record.u, record.v, record.p);
        srec.scatter_ray = Ray(record.p, prng.on_sphere(), ray.time);
        return true;
    }
};

#endif