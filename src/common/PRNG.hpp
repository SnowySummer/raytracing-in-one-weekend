#ifndef COMMON__PRNG_HPP
#define COMMON__PRNG_HPP

#include <common/vec4.hpp>
#include <cstdint>
#include <ctime>

class PRNG {
private:
    uint32_t seed;

public:
    // PRNG constructor
    PRNG() : seed(time(NULL)) {}
    PRNG(uint32_t _seed) : seed(_seed) {}

    // Set seed
    void set_seed(uint32_t _seed) { seed = _seed; }

    // Generate random number
    uint32_t rand() {
        constexpr uint32_t a = 1103515245;
        constexpr uint32_t c = 12345;
        constexpr uint32_t m = (1u << 31);
        seed = (a * seed + c) % m;
        return seed >> 16;
    }

    // Scalar sampling
    float randf() {
        return float(this->rand()) / float(1 << 15);
    }
    float randf(float min, float max) {
        return min + (max-min) * this->randf();
    }
    int randi(float min, float max) {
        return std::floor(randf(min, max+1));
    }

    // 2D sampling
    vec4 square() {
        return vec4(this->randf(-1.0f, 1.0f), this->randf(-1.0f, 1.0f));
    }

    // 3D sampling
    vec4 color() {
        return vec4(this->randf(), this->randf(), this->randf());
    }
    vec4 cube() {
        return vec4(this->randf(-1.0f, 1.0f), this->randf(-1.0f, 1.0f), this->randf(-1.0f, 1.0f));
    }
    vec4 on_sphere() {
        while (true) {
            vec4 r = this->cube();
            if (r.len2() < 1.0f) return vec4::normalise(r);
        }
    }
};

#endif