#ifndef GEOMETRY__COLLECTION__BVH_HPP
#define GEOMETRY__COLLECTION__BVH_HPP

#include "../Geometry.hpp"

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <HitRecord.hpp>
#include <memory>
#include <vector>

class BVH : public Geometry {
public:
    std::shared_ptr<Geometry> left;
    std::shared_ptr<Geometry> right;

public:
    // BVH constructor
    BVH() {}
    BVH(std::shared_ptr<GeometryList> geometry_l) : BVH(geometry_l->geometry_l, 0, geometry_l->size()) {}
    BVH(std::vector<std::shared_ptr<Geometry>>& geometry_l, int start, int end) {
        // Build BBox
        for (int i = start; i < end; i++) {
            bbox = BBox(bbox, geometry_l[i]->bbox);
        }
        
        // Recursion end
        if (end - start == 1) {
            left = right = geometry_l[start];
            return;
        } else if (end - start == 2) {
            left  = geometry_l[start];
            right = geometry_l[start+1];
            return;
        }

        // Find long axis
        int long_axis = -1;
        float axis_len = 0;
        for (int i = 0; i < 3; i++) {
            if (axis_len < bbox.axis[i].size()) {
                axis_len = bbox.axis[i].size();
                long_axis = i;
            }
        }

        // Select comparator and sort
        bool (*comparator)(std::shared_ptr<Geometry>,std::shared_ptr<Geometry>) =
            (long_axis == 0) ? comparator_x
            : (long_axis == 1) ? comparator_y
            : comparator_z;
        std::sort(geometry_l.begin() + start, geometry_l.begin() + end, comparator);

        // Build children
        int mid = (start + end) / 2;
        left = std::make_shared<BVH>(geometry_l, start, mid);
        right = std::make_shared<BVH>(geometry_l, mid, end);
    }

    static bool comparator_x(std::shared_ptr<Geometry> a, std::shared_ptr<Geometry> b) {
        return a->bbox.axis[0].min < b->bbox.axis[0].min;
    }
    static bool comparator_y(std::shared_ptr<Geometry> a, std::shared_ptr<Geometry> b) {
        return a->bbox.axis[1].min < b->bbox.axis[1].min;
    }
    static bool comparator_z(std::shared_ptr<Geometry> a, std::shared_ptr<Geometry> b) {
        return a->bbox.axis[2].min < b->bbox.axis[2].min;
    }

    // Ray intersection
    bool ray_hit(Ray ray, Interval interval, HitRecord& record) const override {
        // Check BBox hit
        if (!bbox.ray_hit(ray, interval)) return false;

        // Check left/right hit
        bool left_hit = left->ray_hit(ray, interval, record);
        bool right_hit;
        if (left_hit) right_hit = right->ray_hit(ray, Interval(interval.min, record.t), record);
        else right_hit = right->ray_hit(ray, interval, record);

        return left_hit || right_hit;
    }
};

#endif