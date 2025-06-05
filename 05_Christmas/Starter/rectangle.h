//
// Created by adith on 02-01-2025.
//
#include "Vector3.hpp"

#ifndef RECTANGLE_H
#define RECTANGLE_H
struct Ray;
struct Rectangle {
    double length;
    double width;
    vec3 _center;
    vec3 _color;
    Rectangle(double length, double width,double thick, vec3 center, vec3 color);
    bool intersect(const Ray& ray, double& t) const;
};


#endif //RECTANGLE_H
