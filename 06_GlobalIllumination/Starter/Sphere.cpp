//
// Created by Peter Zdankin on 13.11.24.
//

#include "Sphere.hpp"

#include "Intersection.hpp"
#include "Ray.hpp"

Material& Sphere::getMaterial() {
    return _material;
}

static double toRadians(double degree){
    return degree/180 * M_PI;
}

static double toDegree(double radians){
    return radians / M_PI * 180;
}

std::optional<Intersection> Sphere::intersect(Ray& ray) {
    vec3 sphere_to_ray = _center - ray._origin;
    double tcenter = dot(sphere_to_ray, ray._direction);
    if(tcenter < 0 ) {
        return {};
    }
    double d_Squared = dot(sphere_to_ray, sphere_to_ray) - tcenter * tcenter;
    if (d_Squared > _radius_squared) {
        return {};
    }

    double distance = sqrt(_radius_squared - d_Squared);
    double t = tcenter - distance;

    if( t < 0) {
        t = tcenter + distance;
    }

    vec3 normal = unit_vector((ray.point_at(t) - _center));

    if(_oneMaterial) {
        return Intersection(_material, normal, t);
    }

    vec3 dir = vec3(ray.point_at(t)-_center).rotateX(_angles.x()).rotateY(toRadians(_angles.y())).rotateZ(toRadians(_angles.z()));
    //double theta = atan2(dir.y(),dir.x());
    double phi = acos(dir.z()/sqrt(_radius_squared));

    phi = toDegree(phi);

    if((phi >= 30 && phi <= 60) || (phi >= 120 && phi <= 150) ){
        return Intersection(_secondaryMaterial,normal,t);
    }
    else{
        return Intersection(_material,normal,t);
    }
}
