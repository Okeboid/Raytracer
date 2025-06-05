//
// Created by Peter Zdankin on 13.11.24.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include <vector>
#include "rectangle.h"

struct Scene{
    // Vector<Sphere> is a dynamically growable list containing Spheres. It behaves like an array that can change its size.
    std::vector<Sphere> _spheres;
    std::vector<Rectangle> _rectangles;
    vec3 _backgroundColor;
    // epsilon is used to counteract float/double imprecisions
    double _epsilon = 0.000000001;

    explicit Scene(vec3 backgroundColor):_backgroundColor(backgroundColor){}
    Scene():_backgroundColor(vec3(0,0,0)){}

    void addSphere(Sphere object);
    void addRectangle(Rectangle object);
    const vec3 getBackgroundColor() const;
    std::optional<Intersection> intersect(const Ray& ray) const;
    vec3 traceRay(const Ray& ray) const;
};

#endif //SCENE_HPP
