#ifndef SCATTERRECORD_HPP
#define SCATTERRECORD_HPP

#include <common/vec4.hpp>
#include <PDF/PDF.hpp>
#include <memory>

class ScatterRecord {
public:
    vec4 attenuation;
    bool skip_pdf;
    std::shared_ptr<PDF> pdf;
    Ray scatter_ray;
};

#endif