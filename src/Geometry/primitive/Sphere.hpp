#ifndef GEOMETRY__PRIMITIVE__SPHERE_HPP
#define GEOMETRY__PRIMITIVE__SPHERE_HPP

#include "../Geometry.hpp"

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/ONB.hpp>
#include <common/Ray.hpp>
#include <Material/Material.hpp>
#include <HitRecord.hpp>

class Sphere : public Geometry {
public:
    Ray center_ray;
    float radius;
    std::shared_ptr<Material> mat;

public:
    // Sphere constructor
    Sphere() : center_ray(Ray(vec4(0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f))), radius(1.0f), mat(nullptr) {}
    Sphere(vec4 _center, float _radius, std::shared_ptr<Material> _mat) :
    center_ray(Ray(_center, vec4(0.0f, 0.0f, 0.0f))), radius(_radius), mat(_mat) {
        vec4 sphere_bbox_radius = vec4(radius, radius, radius);
        bbox = BBox(_center - sphere_bbox_radius, _center + sphere_bbox_radius);
    }
    Sphere(vec4 center1, vec4 center2, float _radius, std::shared_ptr<Material> _mat) :
    center_ray(Ray(center1, center2 - center1)), radius(_radius), mat(_mat) {
        vec4 sphere_bbox_radius = vec4(radius, radius, radius);
        BBox bbox1 = BBox(center1 - sphere_bbox_radius, center1 + sphere_bbox_radius);
        BBox bbox2 = BBox(center2 - sphere_bbox_radius, center2 + sphere_bbox_radius);
        bbox = BBox(bbox1, bbox2);
    }


    // Ray intersection
    bool ray_hit(PRNG& prng, Ray ray, Interval interval, HitRecord& record) const override {
        // Set center point at time
        vec4 center = center_ray.at(ray.time);

        // Check line intersection
        float a = ray.direction.len2();
        float b = vec4::dot(ray.origin - center, ray.direction);
        float c = (ray.origin - center).len2() - radius*radius;
        if (b*b - a*c < 0) return false;

        // Check in interval
        float discr = std::sqrt(b*b - a*c);
        float t = (-b - discr) / a;
        if (!interval.contains(t)) {
            t = (-b + discr) / a;
            if (!interval.contains(t)) return false;
        }

        // Update record
        record.t = t;
        record.p = ray.at(t);
        vec4 outward_normal = (record.p - center) / radius;
        record.set_front_face(ray, outward_normal);
        this->set_uv(outward_normal, record.u, record.v);
        record.mat = mat;

        return true;
    }

    // PDF functions
    vec4 random(PRNG& prng, vec4 origin) override {
        vec4 direction = center_ray.at(0) - origin;
        float dist_2 = direction.len2();
        ONB onb = ONB(direction);
        return onb.transform(random_to_sphere(prng, radius, dist_2));
    }
    float pdf_value(PRNG& prng, vec4 origin, vec4 direction) override {
        // Check visibility
        HitRecord record;
        if (!ray_hit(prng, Ray(origin, direction), Interval(1e-3f, INFINITY), record)) {
            return 0.0f;
        }

        // Calculate solid angle
        float dist_2 = (center_ray.at(0) - origin).len2();
        float cos_theta_max = std::sqrt(1 - radius*radius/dist_2);
        float solid_angle = 2*M_PI*(1 - cos_theta_max);

        return 1 / solid_angle;
    }

private:
    vec4 random_to_sphere(PRNG& prng, float radius, float dist_2) {
        float r1 = prng.randf();
        float r2 = prng.randf();

        float cos_theta_max = std::sqrt(1.0f - radius*radius / dist_2);
        float z = 1 + r2*(cos_theta_max - 1.0f);
        float x = std::cos(2*M_PI*r1) * std::sqrt(1 - z*z);
        float y = std::sin(2*M_PI*r1) * std::sqrt(1 - z*z);

        return vec4(x, y, z);
    }

private:
    void set_uv(vec4 p, float& u, float &v) const {
        float theta = std::acos(-p[1]);
        float phi = M_PI + std::atan2(-p[2], p[0]);

        u = phi / (2 * M_PI);
        v = theta / M_PI;
    }
};

#endif