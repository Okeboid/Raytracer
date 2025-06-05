//
// Created by Peter Zdankin on 13.11.24.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "rectangle.h"


struct Scene{
    std::vector<Sphere> spheres;
    std::vector<Rectangle> rectangles;
    vec3 backgroundColor;
    double epsilon = 0.0000000001;
    explicit Scene(vec3 backgroundColor):backgroundColor(backgroundColor){}
    Scene():backgroundColor(vec3(0,0,0)){}
    void addSphere(Sphere object);
    void addRectangle(Rectangle object);
    const vec3 getBackgroundColor() const;
    std::optional<Intersection> intersect(const Ray& ray) const;
    vec3 traceRay(const Ray& ray, double IoR, int recDepth) const;
};

#endif //SCENE_HPP
