#ifndef HITTABLE__BVH_HPP
#define HITTABLE__BVH_HPP

#include "Hittable.hpp"

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <Hittable/HittableList.hpp>
#include <HitRecord.hpp>
#include <memory>
#include <vector>

class BVH : public Hittable {
public:
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;

public:
    // BVH constructor
    BVH() {}
    BVH(std::shared_ptr<HittableList> hittable_l) : BVH(hittable_l->hittable_l, 0, hittable_l->size()) {}
    BVH(std::vector<std::shared_ptr<Hittable>>& hittable_l, int start, int end) {
        // Build BBox
        for (int i = start; i < end; i++) {
            bbox = BBox(bbox, hittable_l[i]->bbox);
        }
        
        // Recursion end
        if (end - start == 1) {
            left = right = hittable_l[start];
            return;
        } else if (end - start == 2) {
            left  = hittable_l[start];
            right = hittable_l[start+1];
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
        bool (*comparator)(std::shared_ptr<Hittable>,std::shared_ptr<Hittable>) =
            (long_axis == 0) ? comparator_x
            : (long_axis == 1) ? comparator_y
            : comparator_z;
        std::sort(hittable_l.begin() + start, hittable_l.begin() + end, comparator);

        // Build children
        int mid = (start + end) / 2;
        left = std::make_shared<BVH>(hittable_l, start, mid);
        right = std::make_shared<BVH>(hittable_l, mid, end);
    }

    static bool comparator_x(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
        return a->bbox.axis[0].min < b->bbox.axis[0].min;
    }
    static bool comparator_y(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
        return a->bbox.axis[1].min < b->bbox.axis[1].min;
    }
    static bool comparator_z(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
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