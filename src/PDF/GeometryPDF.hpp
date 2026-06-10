#ifndef PDF__GEOMETRY_PDF
#define PDF__GEOMETRY_PDF

#include "PDF.hpp"

#include <Geometry/Geometry.hpp>
#include <memory>

class GeometryPDF : public PDF {
public:
    vec4 origin;
    std::shared_ptr<Geometry> geometry;

public:
    // GeometryPDF constructor
    GeometryPDF(vec4 _origin, std::shared_ptr<Geometry> _geometry) :
    origin(_origin), geometry(_geometry) {}

    
    // Generate direction and PDF
    vec4 generate(PRNG& prng) override {
        return geometry->random(prng, origin);
    }
    float value(PRNG& prng, vec4 direction) override {
        return geometry->pdf_value(prng, origin, direction);
    }
};

#endif