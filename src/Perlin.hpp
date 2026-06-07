#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <common/vec4.hpp>
#include <common/PRNG.hpp>

#define __USE_MATH_DEFINES
#include <cmath>
#include <algorithm>

class Perlin {
public:
    vec4 rand_box[256];
    int sbox_x[256];
    int sbox_y[256];
    int sbox_z[256];

public:
    // Perlin constructor
    Perlin() {}
    Perlin(PRNG& prng) {
        // Generate rand_box
        for (int i = 0; i < 256; i++) {
            rand_box[i] = prng.square();
        }

        // Generate sbox
        for (int i = 0; i < 256; i++) {
            sbox_x[i] = i;
            sbox_y[i] = i;
            sbox_z[i] = i;
        }
        for (int i = 255; 0 < i; i--) {
            std::swap(sbox_x[i], sbox_x[prng.randi(0, i)]);
            std::swap(sbox_y[i], sbox_y[prng.randi(0, i)]);
            std::swap(sbox_z[i], sbox_z[prng.randi(0, i)]);
        }
    }

    float noise(vec4 p) {
        float u = p[0] - std::floor(p[0]);
        float v = p[1] - std::floor(p[1]);
        float w = p[2] - std::floor(p[2]);

        int x = int(std::floor(p[0]));
        int y = int(std::floor(p[1]));
        int z = int(std::floor(p[2]));

        vec4 cube[2][2][2];
        for (int dx = 0; dx < 2; dx++) {
            for (int dy = 0; dy < 2; dy++) {
                for (int dz = 0; dz < 2; dz++) {
                    cube[dx][dy][dz] = rand_box[
                        sbox_x[(x + dx) & 0xFF] ^
                        sbox_y[(y + dy) & 0xFF] ^
                        sbox_z[(z + dz) & 0xFF]
                    ];
                }
            }   
        }

        return perlin_interpolation(cube, u, v, w);
    }

    float turb(vec4 p, int depth) {
        float accum = 0.0f;
        float weight = 1.0f;
        vec4 temp_p = p;
        for (int i = 0; i < depth; i++) {
            accum += weight * noise(temp_p);
            weight *= 0.5f;
            temp_p *= 2.0f;
        }

        return std::fabs(accum);
    }

private:
    float perlin_interpolation(vec4 cube[2][2][2], float u, float v, float w) {
        // Hermitian scaling
        float uu = u*u*(3.0f - 2.0f*u);
        float vv = v*v*(3.0f - 2.0f*v);
        float ww = w*w*(3.0f - 2.0f*w);

        float accum = 0.0f;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    vec4 weight_v = vec4(u-i, v-j, w-k);
                    accum += vec4::dot(
                        weight_v,
                        cube[i][j][k]
                            * (i*u + (1.0f-i)*(1.0f-u))
                            * (j*v + (1.0f-j)*(1.0f-v))
                            * (k*w + (1.0f-k)*(1.0f-w))
                    );
                }
            }
        }
        return accum;
    }
};

#endif