#ifndef HITRECORD_HPP
#define HITRECORD_HPP

#include <vec4.hpp>

class HitRecord {
public:
    float t;
    vec4 p;
    vec4 n;
};

#endif