//Adithye Nambiar (3193667), Soham Kumthekar (3194876), Mohammad Asad Akhtar (3193310)
#include <iostream>
#include <fstream>

const unsigned int width = 100;
const unsigned int height = 100;

void printHeader(std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    ppmFile << "P3" << std::endl; // Magic Number, we're doing a pixelmap here
    ppmFile << width << " " << height << std::endl;   // We need to specify width/height
    ppmFile << "255" << std::endl;    // Maximum value (when this is = 11 instead of 255, we can see gradient with little boxes)
}

struct pixel {
    double r,g,b;
};

// Sets the color of the pixel at x (horizontal) and y (vertical) in the screen
void setColor(pixel* screen, const unsigned int x, const unsigned int y, pixel color)
{
 screen[y * width + x] = color;
}

void drawCircle(pixel* screen, const  int x_circle, const int y_circle, const unsigned int radius, pixel color)
{
    for(int y = y_circle - radius; y <= y_circle + radius; y++) {
        for(int x = x_circle - radius; x <= x_circle + radius; x++) {

                if((x - x_circle) * (x - x_circle) + (y - y_circle) * (y - y_circle) <= radius * radius) {

                    setColor(screen,x,y,color);
                }
            }
    }}

void printScreenToPPMFile(const pixel* screen, std::ofstream& ppmFile, const unsigned int width, const unsigned int height) {
    printHeader(ppmFile, width ,height);
    for( int y = 0; y < height; y++) {
        for( int x = 0; x < width; x++) {
            ppmFile << static_cast<int>(screen[y*width + x].r * 255.0) << " "; //(when this is = 11.0 instead of 255.0, we can see gradient with little boxes)
            ppmFile << static_cast<int>(screen[y*width + x].g * 255.0) << " "; //(when this is = 11.0 instead of 255.0, we can see gradient with little boxes)
            ppmFile << static_cast<int>(screen[y*width + x].b * 255.0) << " "; //(when this is = 11.0 instead of 255.0, we can see gradient with little boxes)
        }
        ppmFile << "\n";
    }
}

int main() {

    pixel screen[width*height];

    std::ofstream ppmFile("output.ppm");


    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            setColor(screen, j, i, {static_cast<double>(i)/height,0,static_cast<double>(j)/width});
        }
    }

    drawCircle(screen, 20,80,5, {0,1,0});

    printScreenToPPMFile(screen, ppmFile, width, height);
    ppmFile.close();


    return 0;
}