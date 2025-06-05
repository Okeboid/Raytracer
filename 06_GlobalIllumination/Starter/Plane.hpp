//
// Created by Peter Zdankin on 01.01.25.
//

#ifndef PLANE_HPP
#define PLANE_HPP
#include "IntersectableObject.hpp"
#include "Material.hpp"
#include "Vector3.hpp"

struct Plane : IntersectableObject {
private:
    void buildLocalFrame();
    vec3 frame1;
    vec3 frame2;
    vec3 center;
    double maxWidth;
    double maxHeight;
    bool isLimited;
    bool oneMaterial;


public:
    vec3 normal;
    double d;
    Material materialPrimary;
    Material materialSecondary;

    Plane(const vec3 &_normal, double _d, const Material &_materialPrimary, const Material &_materialSecondary,
          double _maxWidth, double _maxHeight) : normal(_normal), d(_d), materialPrimary(_materialPrimary),
                                                 materialSecondary(_materialSecondary), maxWidth(_maxWidth),
                                                 maxHeight(_maxHeight) {
        oneMaterial = false;
        buildLocalFrame();
        isLimited = !(_maxWidth == 0 || _maxHeight == 0);
    }

    Plane(const vec3 &_normal, double _d, const Material &_materialPrimary,
          double _maxWidth, double _maxHeight) : normal(_normal), d(_d), materialPrimary(_materialPrimary),
                                                 materialSecondary(_materialPrimary), maxWidth(_maxWidth),
                                                 maxHeight(_maxHeight) {
        oneMaterial = true;
        buildLocalFrame();
        isLimited = !(_maxWidth == 0 || _maxHeight == 0);
    }

    Material &getMaterial() override;

    std::optional<Intersection> intersect( Ray &r) override;

    void rotate(double angle);
};

#endif //PLANE_HPP
