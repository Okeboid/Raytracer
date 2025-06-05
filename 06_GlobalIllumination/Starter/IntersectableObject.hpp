//
// Created by Peter Zdankin on 01.01.25.
//

#ifndef INTERSECTABLEOBJECT_HPP
#define INTERSECTABLEOBJECT_HPP

#include "Material.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"

class IntersectableObject{
public:
    virtual ~IntersectableObject() = default;

    virtual Material& getMaterial() = 0;
    virtual std::optional<Intersection> intersect(Ray& r) = 0;
};

#endif //INTERSECTABLEOBJECT_HPP
