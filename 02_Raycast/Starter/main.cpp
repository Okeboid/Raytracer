#include <iostream>
#include <fstream>

#include "Vector3.hpp"

const unsigned int width = 256;
const unsigned int height = 256 ;

using color = vec3;

// x is the x-position of the pixel
// y is the y-position of the pixel
// color contains values between 0.0 and 1.0 for each of RGB
struct pixel {
    unsigned int x;
    unsigned int y;
    color color;
};



void printHeader(std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    ppmFile << "P3" << std::endl; // Magic Number, we're doing a pixelmap here
    ppmFile << width << " " << height << std::endl;   // We need to specify width/height
    ppmFile << "255" << std::endl;    // Maximum value
}


void setColor(pixel* screen, const unsigned int x, const unsigned int y, vec3 color) {
    screen[width*y + x].color = color;
}

void write_color(std::ostream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

void printScreenToPPMFile(const pixel* screen, std::ofstream& ppmFile) {
    printHeader(ppmFile, width ,height);
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            write_color(ppmFile, screen[width*y + x].color);
        }
        ppmFile << "\n";
    }
}


struct pixel screen[width*height];

int main() {


    for(int i = 0; i < width*height; i++) {
        screen[i].x = i % width;
        screen[i].y = i / width;
        screen[i].color = vec3(0, 0, 100);
    }

    vec3 observer_position = vec3(0, 0, 0);

    for(unsigned int i = 0; i < height; i++) {
        for(unsigned int j = 0; j < width; j++) {
            vec3 pixel_position = vec3(j-width/2.0, i-height/2.0, 100);

            vec3 direction = unit_vector(pixel_position - observer_position);

            direction = (direction + vec3(1,1, 1))/2;

            setColor(screen, j, i, direction);
        }
    }

    std::ofstream ppmFile("output.ppm");
    printScreenToPPMFile(screen, ppmFile);
    ppmFile.close();


    return 0;
}