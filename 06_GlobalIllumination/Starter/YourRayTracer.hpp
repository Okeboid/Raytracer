//
// Created by Peter Zdankin on 13.11.24.
//

#ifndef YOURRAYTRACER_HPP
#define YOURRAYTRACER_HPP
#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Screen.hpp"

struct RaySetup{
    vec3 _topLeft;
    vec3 _rayOrigin;
    vec3 _directionX;
    vec3 _directionY;
};

struct YourRayTracer{
    int _recDepth;
    Camera _camera;
    Scene _scene;
    RaySetup _raySetup;
    RaySetup computeRaySetup(Screen screen);

    YourRayTracer(int recDepth): _recDepth(recDepth){};
    void setCamera(Camera& camera);
    void setScene(Scene& scene);
    void render(Screen& screen);
    void render_row(int y, Screen& screen);
    void renderRealistic(Screen& screen);
    vec3 traceRay(Ray &r);
    vec3 traceRaySampled(Ray &r);
    Ray computeRay(double x, double y);


};


#endif //YOURRAYTRACER_HPP
