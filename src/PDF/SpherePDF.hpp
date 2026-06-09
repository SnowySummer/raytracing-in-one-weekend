#ifndef PDF__SPHERE_PDF_HPP
#define PDF__SPHERE_PDF_HPP

#include "PDF.hpp"

class SpherePDF : public PDF {
public:
    // SpherePDF constructor
    SpherePDF() {}

    vec4 generate(PRNG& prng) override {
        return prng.on_sphere();
    }
    float value(vec4 direction) override {
        return 1.0f / (4 * M_PI);
    }
};

#endif