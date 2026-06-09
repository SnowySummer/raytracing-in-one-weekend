#ifndef MATERIAL__ISOTROPIC_HPP
#define MATERIAL__ISOTROPIC_HPP

#include "Material.hpp"

#include <PDF/SpherePDF.hpp>
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
        srec.skip_pdf = false;
        srec.pdf = std::make_shared<SpherePDF>();
        return true;
    }
    float scatter_pdf(Ray ray, HitRecord record, Ray scatter_ray) override {
        return 1.0f / (4 * M_PI);
    }
};

#endif