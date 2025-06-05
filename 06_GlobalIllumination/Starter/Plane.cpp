//
// Created by Peter Zdankin on 01.01.25.
//

#include "Plane.hpp"

#include <memory>

void Plane::buildLocalFrame() {
    double x = normal.x();
    double y = normal.y();
    double z = normal.z();
    vec3 v;
    if(x != y){
        double temp = x;
        x = y;
        y = temp;
        v = vec3(x,y,z);
    }else if(x != z){
        double temp = x;
        x = z;
        z = temp;
        v = vec3(x,y,z);
    }else if(y != z){
        double temp = y;
        y = z;
        z = temp;
        v = vec3(x,y,z);
    }else{
        v = vec3(0,1,0);
    }
    frame1 = unit_vector(cross(normal,v));
    frame2 = unit_vector(cross(normal,frame1));
    center = vec3() + normal*(-d);
}

Material& Plane::getMaterial(){
    return materialPrimary;
}


 std::optional<Intersection> Plane::intersect( Ray& r){
    double denom = dot(r._direction,normal);

    //Parallel Ray
    if (denom == 0)
        return {};

    double t = -(dot((r._origin - vec3()),normal) + d)/ denom;


    if (t < 0)
        return {};

    vec3 p = r.point_at(t);
    vec3 dir = p - center;
    double x = dot(dir,frame1);
    double y = dot(dir,frame2);

    if(isLimited){
        if( x > maxWidth || x < -maxWidth || y > maxHeight || y < -maxHeight){
            return {};
        }
    }

    if(oneMaterial){
        return Intersection(materialPrimary, normal, t);
    }

    int w = (int)(round(x)) % 2; // w is either 0 or 1
    int h = (int)(round(y)) % 2; // h is either 0 or 1

    // if w and h are equal
    // 00|01
    // 10|11
    // Needed for checkerboard pattern
    if((w + h) % 2 == 0){
        return Intersection(materialPrimary, normal, t);
    }else{
        return Intersection(materialSecondary, normal, t);
    }
}

void Plane::rotate(double angle) {
    // Degree to Rad
    double _angle = angle * M_PI / 180;

    double ca = cos(_angle);
    double sa = sin(_angle);

    double x1 = frame1.x() * ca + frame1.z()*sa;
    double z1 = frame1.z() * ca - frame1.x()*sa;

    //We assume the plane is not using the Y Dimension
    frame1 = vec3(x1, 0, z1);
    frame2 = cross(normal,frame1);

}
