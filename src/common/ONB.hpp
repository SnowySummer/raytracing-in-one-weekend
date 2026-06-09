#ifndef COMMON__ONB_HPP
#define COMMON__ONB_HPP

#include <common/vec4.hpp>

class ONB {
public:
    vec4 axis[3];

public:
    // ONB constructor
    ONB() : axis{vec4(), vec4(), vec4()} {}
    ONB(vec4 n) : axis{vec4(), vec4(), vec4()} {
        vec4 a = (std::fabs(0.9f < vec4::dot(n, vec4(1.0f, 0.0f, 0.0f)))) ? vec4(0.0f, 1.0f, 0.0f) : vec4(1.0f, 0.0f, 0.0f);
        axis[0] = vec4::normalise(vec4::cross(n, a));
        axis[1] = vec4::normalise(vec4::cross(n, axis[0]));
        axis[2] = vec4::normalise(n);
    }

    // Change of basis
    vec4 transform(vec4 u) {
        return u[0]*axis[0] + u[1]*axis[1] + u[2]*axis[2];
    }
};

#endif