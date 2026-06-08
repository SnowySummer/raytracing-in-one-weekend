#ifndef GEOMETRY__COLLECTION__BOX_HPP
#define GEOMETRY__COLLECTION__BOX_HPP

#include <common/vec4.hpp>
#include <Geometry/collection/GeometryList.hpp>
#include <Geometry/primitive/Quad.hpp>
#include <Material/Material.hpp>
#include <memory>

std::shared_ptr<GeometryList> Box(vec4 a, vec4 b, std::shared_ptr<Material> mat) {
    std::shared_ptr<GeometryList> box = std::make_shared<GeometryList>();

    vec4 min = vec4(std::min(a[0], b[0]), std::min(a[1], b[1]), std::min(a[2], b[2]));
    vec4 max = vec4(std::max(a[0], b[0]), std::max(a[1], b[1]), std::max(a[2], b[2]));

    vec4 dx = vec4(max[0] - min[0], 0.0f, 0.0f);
    vec4 dy = vec4(0.0f, max[1] - min[1], 0.0f);
    vec4 dz = vec4(0.0f, 0.0f, max[2] - min[2]);

    box->add(std::make_shared<Quad>(vec4(min[0], min[1], max[2]),  dx,  dy, mat));
    box->add(std::make_shared<Quad>(vec4(max[0], min[1], max[2]), -dz,  dy, mat));
    box->add(std::make_shared<Quad>(vec4(max[0], min[1], min[2]), -dx,  dy, mat));
    box->add(std::make_shared<Quad>(vec4(min[0], min[1], min[2]),  dz,  dy, mat));
    box->add(std::make_shared<Quad>(vec4(min[0], max[1], max[2]),  dx, -dz, mat));
    box->add(std::make_shared<Quad>(vec4(min[0], min[1], min[2]),  dx,  dz, mat));

    return box;
}

#endif