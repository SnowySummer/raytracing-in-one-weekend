#ifndef BBOX_HPP
#define BBOX_HPP

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <algorithm>

class BBox {
public:
    Interval axis[3];

public:
    // BBox constructor
    BBox() : axis{Interval(), Interval(), Interval()} {}
    BBox(vec4 a, vec4 b) : axis{
        Interval(std::min(a[0], b[0]), std::max(a[0], b[0])),
        Interval(std::min(a[1], b[1]), std::max(a[1], b[1])),
        Interval(std::min(a[2], b[2]), std::max(a[2], b[2]))
    } { pad_minimum(); }
    BBox(BBox bbox1, BBox bbox2) : axis{
        Interval(
            std::min(bbox1.axis[0].min, bbox2.axis[0].min),
            std::max(bbox1.axis[0].max, bbox2.axis[0].max)
        ),
        Interval(
            std::min(bbox1.axis[1].min, bbox2.axis[1].min),
            std::max(bbox1.axis[1].max, bbox2.axis[1].max)
        ),
        Interval(
            std::min(bbox1.axis[2].min, bbox2.axis[2].min),
            std::max(bbox1.axis[2].max, bbox2.axis[2].max)
        )
    } { pad_minimum(); }

    bool ray_hit(Ray ray, Interval interval) const {
        for (int i = 0; i < 3; i++) {
            // Check ray intersection
            float t_min = (axis[i].min - ray.origin[i]) / ray.direction[i];
            float t_max = (axis[i].max - ray.origin[i]) / ray.direction[i];

            // Reorder intersection
            float t_0 = std::min(t_min, t_max);
            float t_1 = std::max(t_min, t_max);
            
            // Reduce intersection interval
            if (interval.min < t_0) interval.min = t_0;
            if (t_1 < interval.max) interval.max = t_1;

            // Verify valid interval
            if (interval.max <= interval.min) return false;
        }

        return true;
    }

private:
    void pad_minimum() {
        float pad_min = 1e-4f;
        for (int i = 0; i < 3; i++) {
            if (axis[i].size() < pad_min) axis[i] = axis[i].expand(pad_min);
        }
    }
};

#endif