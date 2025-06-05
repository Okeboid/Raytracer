#include <iostream>
#include <fstream>

#include "Camera.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Vector3.hpp"
#include "Screen.hpp"
#include "YourRayTracer.hpp"
#include "rectangle.h"


int main() {
    const unsigned int height = 2660; //2560
    const unsigned int width = 2600 ; //1600
    Screen screen(width, height);

    // A camera that is slightly behind and above the center point, but looks at 0,0,0
    Camera camera;
    camera.setEyePoint(vec3(0.0,1.0,-15.0));
    camera.setLookAt(vec3(0.0,0.0,0.0));

    // Black background color scene
    Scene scene(vec3(0.5,0.0,0.0));

    //Sphere s1 = Sphere(0.5, vec3{2,-1,2.5},  vec3{1,1,1});
    //Sphere s2 = Sphere(1.0, vec3{-5, -1, 6.2},  vec3{1,0,0});
    //Sphere s3 = Sphere(1.0, vec3{7, -1, 8},  vec3{0,1,1});
    //Sphere s4 = Sphere(1.0, vec3{-12.9, -1, 25.2}, vec3{1,1,0});
    //the round star
    Sphere s5 = Sphere(1.0, vec3{0, 12.5, 2.0},  vec3{1,1,0.2});
    scene.addSphere(s5);
    std::vector<Sphere> spheres;
    for (int i = 13; i >= 2; --i) {
        spheres.emplace_back(i*0.4, vec3{0, 13-i*1.5, 1.0}, vec3{0.0, 0.6, 0});
    }

    for(auto sphere: spheres) {
        scene.addSphere(sphere);
    }
    Rectangle r1=Rectangle(4,2,6,vec3{0,-10.0,-4.5}, vec3{0.34,0.0,0.0});
    scene.addRectangle(r1);
    // After we created a scene, camera, screen, we create a ray tracer that puts it all together and renders the scene
    YourRayTracer renderer;
    renderer.setCamera(camera);
    renderer.setScene(scene);
    renderer.render(screen);

    // I've included a simple way to create png images instead of PPM as PPM takes a lot of space
    screen.saveAsPNG("screen.png");
    return 0;
}
