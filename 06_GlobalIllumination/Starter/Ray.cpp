//
// Created by Peter Zdankin on 13.11.24.
//

#include "Ray.hpp"

#include "Intersection.hpp"
#include "Sphere.hpp"

Ray::Ray(vec3 origin, vec3 direction) : _origin(origin), _direction(direction) {}



vec3 Ray::point_at(double t) const {
    return _origin + t * _direction;
}