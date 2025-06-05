#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
//#include <__ranges/rend.h>

#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Screen.hpp"
#include "YourRayTracer.hpp"

int main() {
    const unsigned int width = 2560;
    const unsigned int height = 1600;
    Screen screen(width, height);
    Camera camera;
    camera.setEyePoint(vec3(0.0,1.5,-4.0));
    camera.setLookAt(vec3(0.0,0.0,0.0));

    Scene scene(vec3(0.0,0.0,0.0), 5);
    std::srand(std::time(nullptr));
    vec3 rotation1 = vec3(std::rand() % 360, std::rand() % 360, std::rand() % 360);
    vec3 rotation2 = vec3(std::rand() % 360, std::rand() % 360, std::rand() % 360);
    vec3 rotation3 = vec3(std::rand() % 360, std::rand() % 360, std::rand() % 360);
    vec3 rotation4 = vec3(std::rand() % 360, std::rand() % 360, std::rand() % 360);
    vec3 rotation5 = vec3(std::rand() % 360, std::rand() % 360, std::rand() % 360);

    Material black = Material(vec3(0.1, 0.1, 0.1), vec3(0.3, 0.3, 0.3), vec3(1, 1, 1), 8, 0.3);
    Material glass = Material(vec3(0.3, 0.3, 0.3), vec3(0.5, 0.5, 0.5), vec3(1, 1, 1), 8, 0.01, 1.52);
    Material red = Material(vec3(1, 0, 0), vec3(1, 0, 0), vec3(1, 1, 1), vec3(1,0,0), 8, 1);
    Material cyan = Material(vec3(0, 1, 1), vec3(0, 1, 1), vec3(1, 1, 1), vec3(0,1,1),8, 1);
    Material yellow = Material(vec3(1, 1, 0), vec3(1, 1, 0), vec3(1, 1, 1),vec3(1,1,0), 8, 1);
    Material green = Material(vec3(0, 1, 0), vec3(0, 1, 0), vec3(1, 1, 1), vec3(0,1,0),8, 1);
    Material white = Material(vec3(0.3, 0.3, 0.3), vec3(0.5, 0.5, 0.5), vec3(1, 1, 1), 8, 1.0);
    Material lamp = Material(vec3(1, 0.91, 0.83), vec3(1, 0.91, 0.83), vec3(1, 0.91, 0.83), vec3(1.0, 0.91, 0.83), 8, 1.0);

    Sphere s1 = Sphere(1.0, vec3{2,-1,2.5},  glass);
    Sphere s2 = Sphere(1.0, vec3{-5, -1, 6.2},  red, black, rotation1);
    Sphere s3 = Sphere(1.0, vec3{7, -1, 8},  cyan, black, rotation2);
    Sphere s4 = Sphere(1.0, vec3{-9.9, -1, 25.2}, yellow, black, rotation3);
    Sphere s5 = Sphere(1.0, vec3{2.9, -1, 15.2},  green, black, rotation4);
    //Sphere s_glass = Sphere(2, vec3{-1,-1,2.5},  glass);

    Sphere spheres[5] = {s1, s2, s3, s4, s5};

    for(auto sphere: spheres) {
        scene.addSphere(sphere);
    }

    Plane plane(unit_vector(vec3(0.0, 1.0, 0.0)), 2, white, black, 0, 0);
    plane.rotate(345);
    scene.addPlane(plane);
    YourRayTracer renderer(5);
    renderer.setCamera(camera);
    renderer.setScene(scene);
    auto start = std::chrono::system_clock::now();
    // Some computation here
    renderer.render(screen);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;

    screen.saveAsPNG("screen.png");

    start = std::chrono::system_clock::now();
    // Some computation here
    renderer.renderRealistic(screen);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end-start;
    end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s"
              << std::endl;

    screen.saveAsPNG("screen_realistic.png");
    return 0;
}
