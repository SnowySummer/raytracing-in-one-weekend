#ifndef PDF__COSINEPDF_HPP
#define PDF__COSINEPDF_HPP

#include "PDF.hpp"

#include <common/ONB.hpp>

class CosinePDF : public PDF {
public:
    ONB onb;

public:
    // CosinePDF constructor
    CosinePDF(ONB _onb) : onb(_onb) {}

    // Generate direction and PDF
    vec4 generate(PRNG& prng) override {
        return onb.transform(prng.cosine_hemisphere());
    }
    float value(PRNG& prng, vec4 direction) override {
        float cos_theta = vec4::dot(vec4::normalise(direction), onb.axis[2]);
        return fmax(0.0f, cos_theta / M_PI);
    }
};

#endif