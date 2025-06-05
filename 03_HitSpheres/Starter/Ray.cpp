//
// Created by Peter Zdankin on 13.11.24.
//

#include "Ray.hpp"

//#include <bits/random.tcc>

#include "Intersection.hpp"
#include "Sphere.hpp"

Ray::Ray(vec3 origin, vec3 direction) : _origin(origin), _direction(direction) {}

/* This is the task. Fill in the intersects method. A ray has an origin point and a direction.
 * A sphere has a center point and a radius, a radius_squared (hint), as well as a colour.
 * If the ray hits no object, return a {} (which indicates that there was no intersection).
 * If the ray hits an object, return a intersection.
 * To find out if a ray hits a sphere, you may (and should) use your math skills.
 * An intersection consists of the colour of the object hit by a ray, the surface normal (a unit_vector pointing from
 * the sphere center to the intersection point) as well as a "_t".
 * If you have an intersection, then _t solves the following:
 *  intersection_point = t * direction + origin
 *
 */
std::optional<Intersection> Ray::intersects(const Sphere& sphere) const {
    vec3 L=sphere._center-_origin;
    double tc=dot(L,_direction);
    if(tc<0) return {};
    double dsqr=L.length()*L.length() - tc*tc;
    if(dsqr>sphere._radius_squared) return {};
    else if (dsqr<sphere._radius_squared) {
        double sml=sqrt(sphere._radius_squared-dsqr);
        double p1=tc-sml,p2=tc+sml;
        vec3 p=_origin+(p1*_direction);
        vec3 norm=unit_vector(p-sphere._center);
        return Intersection{sphere._color, norm, p1};
    }
    else {
        vec3 p=_origin+(tc*_direction);
        vec3 norm=unit_vector(p-sphere._center);
        return Intersection{sphere._color, norm, tc};
    }

}



vec3 Ray::point_at(float t) const {
    return _origin + t * _direction;
}