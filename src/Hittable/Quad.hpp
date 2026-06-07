#ifndef HITTABLE__QUAD_HPP
#define HITTABLE__QUAD_HPP

#include "Hittable.hpp"

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <Material/Material.hpp>
#include <HitRecord.hpp>

class Quad : public Hittable {
public:
    vec4 Q;
    vec4 u;
    vec4 v;
    std::shared_ptr<Material> mat;

private:
    vec4 n;
    vec4 w;
    float D;

public:
    // Quad constructor
    Quad() : Q(vec4(0.0f, 0.0f, 0.0f)), u(vec4(0.0f, 0.0f, 0.0f)), v(vec4(0.0f, 0.0f, 0.0f)), mat(nullptr) {}
    Quad(vec4 _Q, vec4 _u, vec4 _v, std::shared_ptr<Material> _mat) : Q(_Q), u(_u), v(_v), mat(_mat) {
        // Construct bounding box
        BBox bbox1 = BBox(Q, Q + u + v);
        BBox bbox2 = BBox(Q + u, Q + v);
        bbox = BBox(bbox1, bbox2);

        // Calculate quad private members
        n = vec4::cross(u, v);
        w = n / n.len2();
        n = vec4::normalise(n);
        D = vec4::dot(n, Q);
    }


    // Ray intersection
    bool ray_hit(Ray ray, Interval interval, HitRecord& record) const override {
        // Check for parallel rays
        if (std::fabs(vec4::dot(n, ray.direction)) < 1e-8f) return false;

        // Fetch plane intersection point
        float t = (D - vec4::dot(n, ray.origin)) / vec4::dot(n, ray.direction);
        if (!interval.contains(t)) return false;

        // Check point in quad
        vec4 p = ray.at(t) - Q;
        float alpha = vec4::dot(w, vec4::cross(p, v));
        float beta  = vec4::dot(w, vec4::cross(u, p));
        if (!Interval(0, 1).contains(alpha) || !Interval(0, 1).contains(beta)) return false;

        // Update record
        record.t = t;
        record.p = ray.at(t);
        vec4 outward_normal = n;
        record.set_front_face(ray, outward_normal);
        record.u = alpha;
        record.v = beta;
        record.mat = mat;

        return true;
    }
};

#endif