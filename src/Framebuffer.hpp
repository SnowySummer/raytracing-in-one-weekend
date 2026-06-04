#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <vec4.hpp>
#include <vector>

class Framebuffer {
public:
    int width;
    int height;
    std::vector<vec4> colorbuffer;

public:
    // Framebuffer constructor
    Framebuffer() : width(1), height(1), colorbuffer(std::vector<vec4>(1)) {}
    Framebuffer(int _width, int _height) :
    width(_width), height(_height),
    colorbuffer(std::vector<vec4>(_width * _height)) {}

    // Member access
    int size() const { return width * height; }
    vec4  operator[](int index) const { return colorbuffer[index]; }
    vec4& operator[](int index) { return colorbuffer[index]; }
    vec4  get(int x, int y) const { return colorbuffer[x + y * width]; }
    vec4& get(int x, int y) { return colorbuffer[x + y * width]; }

    // Render functions
    void clear(vec4 color) {
        for (int i = 0; i < this->size(); i++) {
            colorbuffer[i] = color;
        }
    }
};

#endif