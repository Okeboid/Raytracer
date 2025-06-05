//
// Created by Peter Zdankin on 13.11.24.
//


#include "YourRayTracer.hpp"

#include <future>

#include "Ray.hpp"
#include <thread>


RaySetup YourRayTracer::computeRaySetup(const Screen screen) {
    RaySetup rs;
    vec3 forwardDir = _camera.getViewDir();
    vec3 upDir = _camera.getUpDir();
    double openingAngle = _camera.getFoV()* M_PI / 180;
    rs._rayOrigin = _camera.getEyePoint();
    double aspectRatio = ((double) screen.getWidth())/ ((double) screen.getHeight());
    vec3 rightDir = -cross(forwardDir,upDir);
    vec3 rowVector = rightDir*2.0*tan(openingAngle/2.0) * aspectRatio;
    vec3 columnVector = upDir * 2.0 * tan(openingAngle/2.0);
    rs._directionX = rowVector/((double)screen.getWidth());
    rs._directionY = columnVector*(-1.0)/((double)screen.getHeight());
    rs._topLeft = vec3() + (forwardDir - (rowVector - columnVector)*0.5);

    return rs;
}

void YourRayTracer::setCamera(Camera& camera) {
    this->_camera = camera;
}

void YourRayTracer::setScene(Scene& scene) {
    this->_scene = scene;
}

void YourRayTracer::render(Screen& screen) {
    _raySetup = computeRaySetup(screen);
    for(uint64_t y = 0; y < screen.getHeight(); ++y) {
        for(uint64_t x = 0; x < screen.getWidth(); ++x) {
            vec3 color;
            Ray r = computeRay(x,y);
            color = traceRay(r);
            screen.setPixel(x, y, color);
        }
    }
}

void YourRayTracer::render_row(int y, Screen& screen) {
    for(uint64_t x = 0; x < screen.getWidth(); ++x) {
        vec3 color;
        Ray r = computeRay(x,y);
        color = traceRaySampled(r);
        color.clamp(0.0,1.0);
        screen.setPixel(x, y, color);
    }
}

void YourRayTracer::renderRealistic(Screen& screen) {
    _raySetup = computeRaySetup(screen);
    std::vector<std::future<void>> futures;
    futures.reserve(screen.getHeight());
    for(uint64_t y = 0; y < screen.getHeight(); ++y) {
        futures.push_back(std::async(std::launch::async,&YourRayTracer::render_row, this, y,std::ref(screen)));
    }
    for (auto& future : futures) {
        future.get();
    }
}

vec3 YourRayTracer::traceRay(Ray &r){
    return _scene.traceRay(r, 1.0, _recDepth);
}

vec3 YourRayTracer::traceRaySampled(Ray &r){
    return _scene.traceRayRealistic(r, 1.0, _recDepth);
}


Ray YourRayTracer::computeRay(double x, double y){
    vec3 direction = unit_vector((_raySetup._topLeft + _raySetup._directionX*x + _raySetup._directionY * y) - vec3());
    return Ray(_raySetup._rayOrigin, direction);
}