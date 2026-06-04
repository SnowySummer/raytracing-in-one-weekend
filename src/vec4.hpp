#ifndef VEC4_HPP
#define VEC4_HPP

#define _USE_MATH_DEFINES
#include <cmath>

class vec4 {
private:
    float e[4];

public:
    // vec4 constructor
    vec4() : e{0.0f, 0.0f, 0.0f, 0.0f} {}
    vec4(float e0, float e1, float e2) : e{e0, e1, e2, 0.0f} {}
    vec4(float e0, float e1, float e2, float e3) : e{e0, e1, e2, e3} {}

    // Member access
    float  operator[](int index) const { return e[index]; }
    float& operator[](int index) { return e[index]; }

    // Norm operation
    float len2() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2] + e[3]*e[3]; }
    float len()  const { return std::sqrt(this->len2()); }
    static vec4 normalise(vec4 u) { return u / u.len(); }

    // Geometric operation
    static float dot(vec4 u, vec4 v) {
        return u[0] * v[0] + u[1] * v[1] + u[2] * v[2] + u[3] * v[3];
    }
    static vec4 cross(vec4 u, vec4 v) {
        return vec4(
            u[1]*v[2] - u[2]*v[1],
            u[2]*v[0] - u[0]*v[2],
            u[0]*v[1] - u[1]*v[0]
        );
    }

    // Operator overload
    friend vec4  operator+(vec4 u);
    friend vec4  operator-(vec4 u);
    friend vec4  operator+(vec4 u, vec4 v);
    friend vec4  operator-(vec4 u, vec4 v);
    friend vec4  operator*(vec4 u, vec4 v);
    friend vec4  operator*(float t, vec4 u);
    friend vec4  operator*(vec4 u, float t);
    friend vec4  operator/(vec4 u, float t);
    friend vec4& operator+=(vec4& u, vec4 v);
    friend vec4& operator-=(vec4& u, vec4 v);
    friend vec4& operator*=(vec4& u, vec4 v);
    friend vec4& operator*=(vec4& u, float t);
    friend vec4& operator/=(vec4& u, float t);
};

// vec4 operator overlaod implementation
inline vec4 operator+(vec4 u) {
    return u;
}
inline vec4 operator-(vec4 u) {
    return vec4(-u[0], -u[1], -u[2], -u[3]);
}
inline vec4 operator+(vec4 u, vec4 v) {
    return vec4(u[0] + v[0], u[1] + v[1], u[2] + v[2], u[3] + v[3]);
}
inline vec4 operator-(vec4 u, vec4 v) {
    return vec4(u[0] - v[0], u[1] - v[1], u[2] - v[2], u[3] - v[3]);
}
inline vec4 operator*(vec4 u, vec4 v) {
    return vec4(u[0] * v[0], u[1] * v[1], u[2] * v[2], u[3] * v[3]);
}
inline vec4 operator*(float t, vec4 u) {
    return vec4(t * u[0], t * u[1], t * u[2], t * u[3]);
}
inline vec4 operator*(vec4 u, float t) {
    return vec4(u[0] * t, u[1] * t, u[2] * t, u[3] * t);
}
inline vec4 operator/(vec4 u, float t) {
    return vec4(u[0] / t, u[1] / t, u[2] / t, u[3] / t);
}
inline vec4& operator+=(vec4& u, vec4 v) {
    u[0] += v[0]; u[1] += v[1]; u[2] += v[2]; u[3] += v[3];
    return u;
}
inline vec4& operator-=(vec4& u, vec4 v) {
    u[0] -= v[0]; u[1] -= v[1]; u[2] -= v[2]; u[3] -= v[3];
    return u;
}
inline vec4& operator*=(vec4& u, vec4 v) {
    u[0] *= v[0]; u[1] *= v[1]; u[2] *= v[2]; u[3] *= v[3];
    return u;
}
inline vec4& operator*=(vec4& u, float t) {
    u[0] *= t; u[1] *= t; u[2] *= t; u[3] *= t;
    return u;
}
inline vec4& operator/=(vec4& u, float t) {
    u[0] /= t; u[1] /= t; u[2] /= t; u[3] /= t;
    return u;
}

#endif