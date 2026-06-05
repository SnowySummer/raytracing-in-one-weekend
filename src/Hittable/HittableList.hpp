#ifndef HITTABLE__HITTABLELIST_HPP
#define HITTABLE__HITTABLELIST_HPP

#include "Hittable.hpp"

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <HitRecord.hpp>
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> hittable_l;

public:
    // HittableList constructor
    HittableList() : hittable_l(std::vector<std::shared_ptr<Hittable>>()) {}

    // Manage hittable list
    void add(std::shared_ptr<Hittable> hittable) { hittable_l.push_back(hittable); }

    // Ray intersection
    bool ray_hit(Ray ray, Interval interval, HitRecord& record) const override {
        bool is_hit = false;
        HitRecord temp_record;
        for (int i = 0; i < hittable_l.size(); i++) {
            if (hittable_l[i]->ray_hit(ray, interval, temp_record)) {
                is_hit = true;
                interval.max = temp_record.t;
                record = temp_record;
            }
        }
        return is_hit;
    }
};

#endif