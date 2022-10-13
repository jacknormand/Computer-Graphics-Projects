#include<stdio.h>
#include "v3math.h"
int main();

// TODO 
// parse input.csv
// error suite
// draw sphere
// draw plane

// DONE
// none

// this ray will be sent through each pixel, and see what color we get
// ray goes from camera to pixel and see what it intersects, find color (background color if nothing)
typedef struct ray
{
    // ray origin (A) (vector) (0,0,0 for camera)
    float origin[3];

    // ray direction (B) (vector) (along z axis for camera)
    float direction[3];

    // float num (t) (distance from origin?)
    int distance;

    // p(t) = A + t*B (p is position) (points at stuff) (might be moved outta here idk)
    // all the points p lying on the ray satisfy the ray equation

}ray;



int main() {

    // these values read from arg in later
    int sceneWidth = 400;
    int sceneHeight = 400;

    int image[sceneWidth][sceneHeight];

    // camera info also parsed from file
    float cameraWidth = .5;
    float cameraHeight = .5;
    float focalLength = 1.0;
    float origin[] = {0,0,0};
    float horizontal[] = {cameraWidth, 0, 0};
    float vertical[] = {0, cameraHeight, 0};

    // origin- vector-horizontal/2 - vertical/2 - (0,0,focallength) = lowerleft corner
    float horizontalHalved[] = {horizontal[0], horizontal[1], horizontal[2]};
    float verticalHalved[] = {vertical[0], vertical[1], vertical[2]};
    float FocalLengthZ[] = {0,0,focalLength};
    float lowerLeft[] = {0,0,0};
    // half
    v3_scale(horizontalHalved, .5);
    v3_scale(verticalHalved, .5);
    // math subtract
    v3_subtract(lowerLeft, origin, horizontalHalved);
    v3_subtract(lowerLeft, lowerLeft, verticalHalved);
    v3_subtract(lowerLeft, lowerLeft, FocalLengthZ);


    // background color (need to divide by 255 for math, then multiply by 255 to get back to value to write)
    // float pixelColor[] = {80,200,255};

    char* outputFileName = "hello.ppm";
    FILE* outputFile;

    // open up
    outputFile = fopen(outputFileName, "w");

    // ppm header
    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", sceneWidth, sceneHeight);
    fprintf(outputFile, "%d\n", 255);

    // index vars
    float widthIndex;
    float heightIndex;

    // iterate over pixels in image, one a time,  shooting a ray 
    // through the center of the pixel out into the scene, 
    // looking for intersections between each ray and the scene geometry.

    // For loop vertical
    for ( heightIndex = sceneHeight-1; heightIndex >= 0; heightIndex--)
    {
        // For loop horizontal
        for (widthIndex = 0; widthIndex < sceneWidth; widthIndex++)
        {
            pixelColor[0] = (widthIndex/(sceneWidth-1));
            //printf("1:%f\n", pixelColor[0]);
            pixelColor[1] = (heightIndex/(sceneHeight-1));
            //printf("2:%f\n", pixelColor[1]);
            pixelColor[2] = .25;
            //printf("3:%f\n", pixelColor[2]);
            fprintf(outputFile, "%f %f %f ", pixelColor[0]*255, pixelColor[1]*255, pixelColor[2]*255);
        }
        fprintf(outputFile, "\n");
    }


    fclose(outputFile);
    return 0;
}