#ifndef GEOMETRY__TRANSFORM__ROTATEY_HPP
#define GEOMETRY__TRANSFORM__ROTATEY_HPP

#include "../Geometry.hpp"

#include <common/vec4.hpp>
#include <memory>

class RotateY : public Geometry {
public:
    std::shared_ptr<Geometry> geometry;
    float cos_theta;
    float sin_theta;

public:
    // RotateY constructor
    RotateY() : geometry(nullptr), cos_theta(1.0f), sin_theta(0.0f) {}
    RotateY(std::shared_ptr<Geometry> _geometry, float theta) :
    geometry(_geometry),
    cos_theta(std::cos(theta)), sin_theta(std::sin(theta)) {
        bbox = geometry->bbox;
        vec4 min = vec4( INFINITY,  INFINITY,  INFINITY);
        vec4 max = vec4(-INFINITY, -INFINITY, -INFINITY);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++) {
                    // Get BBox point
                    float x = (1.0f-i)*bbox.axis[0].min + i*(bbox.axis[0].max);
                    float y = (1.0f-j)*bbox.axis[1].min + j*(bbox.axis[1].max);
                    float z = (1.0f-k)*bbox.axis[2].min + k*(bbox.axis[2].max);

                    // Translate BBox point
                    x = cos_theta * x + sin_theta * z;
                    z = -sin_theta * x + cos_theta * z;

                    // Find BBox
                    min = vec4(std::min(min[0], x), std::min(min[1], y), std::min(min[2], z));
                    max = vec4(std::max(max[0], x), std::max(max[1], y), std::max(max[2], z));
                }
            }
        }

        bbox = BBox(min, max);
    }

    // Ray intersection
    bool ray_hit(PRNG& prng, Ray ray, Interval interval, HitRecord& record) const override {
        // Rotate ray
        vec4 ray_origin = vec4(
            cos_theta * ray.origin[0] - sin_theta * ray.origin[2],
            ray.origin[1],
            sin_theta * ray.origin[0] + cos_theta * ray.origin[2]
        );
        
        vec4 ray_direction = vec4(
            cos_theta * ray.direction[0] - sin_theta * ray.direction[2],
            ray.direction[1],
            sin_theta * ray.direction[0] + cos_theta * ray.direction[2]
        );

        Ray rotate_ray = Ray(ray_origin, ray_direction, ray.time);

        // Check intersection
        if (!geometry->ray_hit(prng, rotate_ray, interval, record)) return false;

        // Rotate record value
        record.p = vec4(
            cos_theta * record.p[0] + sin_theta * record.p[2],
            record.p[1],
            -sin_theta * record.p[0] + cos_theta * record.p[2]
        );
        
        record.n = vec4(
            cos_theta * record.n[0] + sin_theta * record.n[2],
            record.n[1],
            -sin_theta * record.n[0] + cos_theta * record.n[2]
        );

        return true;
    }
};

#endif