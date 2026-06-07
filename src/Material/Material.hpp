#ifndef MATERIAL__MATERIAL_HPP
#define MATERIAL__MATERIAL_HPP

#include <common/PRNG.hpp>
#include <common/Ray.hpp>
#include <HitRecord.hpp>
#include <ScatterRecord.hpp>

class Material {
public:
    // Material virtual destructor
    virtual ~Material() {}

    // Light emission
    virtual vec4 light_emission(float u, float v, vec4 p) = 0;

    // Ray scattering
    virtual bool ray_scatter(PRNG& prng, Ray ray, HitRecord record, ScatterRecord& srec) const = 0;
};

#endif