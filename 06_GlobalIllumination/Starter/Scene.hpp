//
// Created by Peter Zdankin on 13.11.24.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include "Vector3.hpp"
#include "Sphere.hpp"
#include "Intersection.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include <vector>




struct Scene{
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;
    vec3 backgroundColor;
    double epsilon = 0.0000000001;
    int samples;
    explicit Scene(vec3 backgroundColor):backgroundColor(backgroundColor), samples(1){}
    Scene():backgroundColor(vec3(0,0,0)), samples(1){}
    Scene (vec3 backgroundColor, int samples): backgroundColor(backgroundColor), samples(samples){}

    void addSphere(Sphere &object);
    void addPlane(Plane &object);
    const vec3 getBackgroundColor() const;
    std::optional<Intersection> intersect(Ray &ray) const;
    vec3 traceRay(Ray &ray, double IoR, int recDepth) const;
    vec3 traceRayRealistic(Ray &ray, double IoR, int recDepth) const;
};

#endif //SCENE_HPP
