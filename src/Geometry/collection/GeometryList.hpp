#ifndef GEOMETRY__COLLECTION__GEOMETRYLIST_HPP
#define GEOMETRY__COLLECTION__GEOMETRYLIST_HPP

#include "../Geometry.hpp"

#include <common/Interval.hpp>
#include <common/vec4.hpp>
#include <common/Ray.hpp>
#include <HitRecord.hpp>
#include <memory>
#include <vector>

class GeometryList : public Geometry {
public:
    std::vector<std::shared_ptr<Geometry>> geometry_l;

public:
    // GeometryList constructor
    GeometryList() : geometry_l(std::vector<std::shared_ptr<Geometry>>()) {}

    // Manage geometry list
    void add(std::shared_ptr<Geometry> geometry) {
        geometry_l.push_back(geometry);

        // Update BBox
        bbox = BBox(bbox, geometry->bbox);
    }
    size_t size() const { return geometry_l.size(); }

    // Ray intersection
    bool ray_hit(PRNG& prng, Ray ray, Interval interval, HitRecord& record) const override {
        bool is_hit = false;
        HitRecord temp_record;
        for (int i = 0; i < geometry_l.size(); i++) {
            if (geometry_l[i]->ray_hit(prng, ray, interval, temp_record)) {
                is_hit = true;
                interval.max = temp_record.t;
                record = temp_record;
            }
        }
        return is_hit;
    }

    // PDF functions
    vec4 random(PRNG& prng, vec4 origin) override {
        int i = prng.randi(0, geometry_l.size()-1);
        return geometry_l[i]->random(prng, origin);
    }
    float pdf_value(PRNG& prng, vec4 origin, vec4 direction) override {
        float sum = 0.0f;
        for (int i = 0; i < geometry_l.size(); i++) {
            sum += geometry_l[i]->pdf_value(prng, origin, direction);
        }
        return sum / geometry_l.size();
    }
};

#endif