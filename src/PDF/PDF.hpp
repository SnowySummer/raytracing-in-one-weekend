#ifndef PDF__PDF_HPP
#define PDF__PDF_HPP

#include <common/vec4.hpp>
#include <common/PRNG.hpp>

class PDF {
public:
    // PDF virtual destructor
    virtual ~PDF() {}

    // Generate direction and PDF
    virtual vec4 generate(PRNG& prng) = 0;
    virtual float value(PRNG& prng, vec4 direction) = 0;
};

#endif