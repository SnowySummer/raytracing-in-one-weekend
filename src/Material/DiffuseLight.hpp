#ifndef MATERIAL__DIFFUSELIGHT_HPP
#define MATERIAL__DIFFUSELIGHT_HPP

#include "Material.hpp"

#include <common/vec4.hpp>

class DiffuseLight : public Material {
public:
    std::shared_ptr<Texture> light;

public:
    // DiffuseLight constructor
    DiffuseLight() : light(nullptr) {}
    DiffuseLight(vec4 _light) : light(std::make_shared<SolidColorTexture>(_light)) {}

    // Light emission
    vec4 light_emission(Ray ray, HitRecord record, float u, float v, vec4 p) override {
        if (!record.front_face) return vec4(0.0f, 0.0f, 0.0f);
        return light->value(u, v, p);
    }

    // Ray scattering
    bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const override {
        return false;
    }
    virtual float scatter_pdf(Ray ray, HitRecord record, Ray scatter_ray) override {
        return 0.0f;
    }
};

#endif