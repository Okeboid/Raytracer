//
// Created by Peter Zdankin on 13.11.24.
//

#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <utility>

#include "IntersectableObject.hpp"
#include "Material.hpp"
#include "Vector3.hpp"
#include "Ray.hpp"

struct Sphere: IntersectableObject {
    double _radius;
    double _radius_squared;
    vec3 _center;
    Material _material;
    Material _secondaryMaterial;
    vec3 _angles;
    bool _oneMaterial;

    Sphere(double radius, vec3 center, Material material): _radius(radius), _center(center), _radius_squared(radius*radius), _material(material), _secondaryMaterial(material), _oneMaterial(true) {}
    Sphere(double radius, vec3 center, Material primaryMaterial, Material secondaryMaterial): _radius(radius), _center(center), _radius_squared(radius*radius), _material(primaryMaterial), _secondaryMaterial(secondaryMaterial), _oneMaterial(false) {}
    Sphere(double radius, vec3 center, Material primaryMaterial, Material secondaryMaterial, vec3 angles): _radius(radius), _center(center), _radius_squared(radius*radius), _material(primaryMaterial), _secondaryMaterial(secondaryMaterial), _oneMaterial(false), _angles(angles) {}


    Material& getMaterial() override;
    std::optional<Intersection> intersect(Ray &r) override;
};




#endif //SPHERE_HPP
