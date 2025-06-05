//
// Created by adith on 02-01-2025.
//
#include "Vector3.hpp"
#include "Material.hpp"

#ifndef RECTANGLE_H
#define RECTANGLE_H
struct Ray;
struct Rectangle {
    double length;
    double width;
    double thick;
    vec3 _center;
    Material _material;
    Rectangle(double length,double width,double thick, vec3 center, Material material): length(length),thick(thick),width(width), _center(center), _material(material) {}
    bool intersect(const Ray& ray, double& t) const;
};


#endif //RECTANGLE_H
