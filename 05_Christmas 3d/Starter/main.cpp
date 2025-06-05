#include <iostream>
#include <fstream>
//#include <__ranges/rend.h>
#include <chrono>


#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Screen.hpp"
#include "YourRayTracer.hpp"
#include "rectangle.h"


int main() {
    const unsigned int width = 2600;
    const unsigned int height = 3660;
    Screen screen(width, height);
    Camera camera;
    camera.setEyePoint(vec3(0.0,11.0,-17.0));
    camera.setLookAt(vec3(0.0,-0.5,0.0));

    Scene scene(vec3(0.5,0.0,0.0));

    Material red = Material(vec3(0.34, 0, 0), vec3(0.34, 0, 0), vec3(1, 1, 1), 18, 0.9);

    Material yellow = Material(vec3(1, 1, 0), vec3(1, 1, 0), vec3(1, 1, 1), 8, 0.9);
    Material green = Material(vec3(0, 1, 0), vec3(0, 0, 0.2), vec3(0.5, 0.5, 0.5), 8, 0.8);




    //the round star
    Sphere s5 = Sphere(1.2, vec3{0, 8.5, 12.0}, yellow);
    scene.addSphere(s5);
    //the tree
    std::vector<Sphere> spheres;
    for (int i = 13; i >= 2; --i) {
        spheres.emplace_back(sqrt(i*1.8), vec3{0, static_cast<double>(10-i*2 ), 11.0}, green);
    }

    for(auto sphere: spheres) {
        scene.addSphere(sphere);
    }

    //the bark
    Rectangle r1=Rectangle(3,1.5,6,vec3{0,-5.0,-4.5}, red);
    scene.addRectangle(r1);

    YourRayTracer renderer(6);
    renderer.setCamera(camera);
    renderer.setScene(scene);
    auto start = std::chrono::system_clock::now();
    // Some computation here
    renderer.render(screen);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;

    screen.saveAsPNG("screen.png");
    return 0;
}