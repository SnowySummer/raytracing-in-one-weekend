#ifndef SCATTERRECORD_HPP
#define SCATTERRECORD_HPP

#include <common/vec4.hpp>
#include <common/Ray.hpp>

class ScatterRecord {
public:
    vec4 attenuation;
    Ray scatter_ray;
};

#endif