#ifndef VEC4_HPP
#define VEC4_HPP

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
};

#endif