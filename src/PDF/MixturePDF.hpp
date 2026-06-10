#ifndef PDF__MIXTURE_PDF
#define PDF__MIXTURE_PDF

#include "PDF.hpp"

#include <memory>

class MixturePDF : public PDF {
public:
    std::shared_ptr<PDF> pdf0;
    std::shared_ptr<PDF> pdf1;

public:
    // MixturePDF constructor
    MixturePDF(std::shared_ptr<PDF> _pdf0, std::shared_ptr<PDF> _pdf1) :
    pdf0(_pdf0), pdf1(_pdf1) {}

        // Generate direction and PDF
    vec4 generate(PRNG& prng) override {
        if (prng.randf() < 0.5f) return pdf0->generate(prng);
        else                     return pdf1->generate(prng);
    }
    float value(PRNG& prng, vec4 direction) override {
        return 0.5f * pdf0->value(prng, direction) + 0.5f * pdf1->value(prng, direction);
    }
};

#endif