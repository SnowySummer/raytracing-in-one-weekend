#ifndef RAY_HPP
#define RAY_HPP

#include <vec4.hpp>

class Ray {
public:
    vec4 origin;
    vec4 direction;

public:
    // Ray constructor
    Ray() : origin(vec4(0.0f, 0.0f, 0.0f)), direction(vec4(0.0f, 0.0f, -1.0f)) {}
    Ray(vec4 _origin, vec4 _direction) : origin(_origin), direction(_direction) {}

    // Fetch raypoint
    vec4 at(float t) const { return origin + t * direction; }
};

#endif