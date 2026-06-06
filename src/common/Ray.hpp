#ifndef COMMON__RAY_HPP
#define COMMON__RAY_HPP

#include <common/vec4.hpp>

class Ray {
public:
    vec4 origin;
    vec4 direction;
    float time;

public:
    // Ray constructor
    Ray() : origin(vec4(0.0f, 0.0f, 0.0f)), direction(vec4(0.0f, 0.0f, -1.0f)), time(0.0f) {}
    Ray(vec4 _origin, vec4 _direction) : origin(_origin), direction(_direction), time(0.0f) {}
    Ray(vec4 _origin, vec4 _direction, float _time) :
    origin(_origin), direction(_direction), time(_time) {}

    // Fetch raypoint
    vec4 at(float t) const { return origin + t * direction; }
};

#endif