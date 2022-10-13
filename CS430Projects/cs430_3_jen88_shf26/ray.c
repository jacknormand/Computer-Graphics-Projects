#include<stdio.h>
#include "v3math.h"

// TODO 
// parse input.csv
// error suite
// draw sphere
// draw plane
// set background color to black

// DONE
// none

// this ray will be sent through each pixel, and see what color we get
// ray goes from camera to pixel and see what it intersects, find color (background color if nothing)
typedef struct ray
{
    // ray origin (A) (vector) (0,0,0 for camera)
    float* origin;

    // ray direction (B) (vector) (along z axis for camera)
    float* direction;

    // float num (t) (distance from origin?)
    //int distance;

    // p(t) = A + t*B (p is position) (points at stuff) (might be moved outta here idk)
    // all the points p lying on the ray satisfy the ray equation

}ray;

int main();
void getColor(float* dst, ray inputRay);


void getColor(float* dst, ray inputRay)
{
    // intersection


    // nomralize direction
    float normalized[] = {0,0,0};
    // set colors
    float colorWhite[] = {1.0,1.0,1.0};
    float colorRed[] = {1,0,1};
    v3_normalize(normalized, inputRay.direction);

    // get it done
    float lenT = .5 * (normalized[1] + 1.0);
    float neglenT = 1 - lenT;
    v3_scale(colorWhite, neglenT);
    v3_scale(colorRed, lenT);
    v3_add(dst, colorRed, colorWhite);

}



int main()
{
    // these values read from arg in later
    int sceneWidth = 400;
    int sceneHeight = 400;

    //int image[sceneWidth][sceneHeight];

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
    // this changes btw these numbers are a default blue
    float pixelColor[] = {80,200,255};

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
    float xVal;
    float yVal;
    float directionVar[] = {lowerLeft[0],lowerLeft[1],lowerLeft[2]};
    float horizontalTimesX[] = {horizontal[0],horizontal[1],horizontal[2]};
    float verticalTimesY[] = {vertical[0],vertical[1],vertical[2]};

    // ray
    ray currentRay;
    currentRay.origin = origin;

    // iterate over pixels in image, one a time,  shooting a ray 
    // through the center of the pixel out into the scene, 
    // looking for intersections between each ray and the scene geometry.
    //printf("1:%f\n", pixelColor[0]);
    //printf("2:%f\n", pixelColor[1]);
    //printf("3:%f\n", pixelColor[2]);

    // For loop vertical
    for ( heightIndex = sceneHeight-1; heightIndex >= 0; heightIndex--)
    {
        // For loop horizontal
        for (widthIndex = 0; widthIndex < sceneWidth; widthIndex++)
        {
            xVal = (widthIndex/(sceneWidth-1));
            yVal = (heightIndex/(sceneHeight-1));

            // do some quick maf
            v3_scale(horizontalTimesX, xVal);
            v3_scale(verticalTimesY, yVal);
            v3_add(directionVar, directionVar, horizontalTimesX);
            v3_add(directionVar, directionVar, verticalTimesY);
            v3_subtract(directionVar, directionVar, origin);

            // set ray direciton
            currentRay.direction = directionVar;

            //currentRay.direction = directionVar;
            // printf("1:%f\n", currentRay.direction[0]);
            // printf("2:%f\n", currentRay.direction[1]);
            // printf("3:%f\n", currentRay.direction[2]);

            // get ray color 
            getColor(pixelColor, currentRay); 
            
            fprintf(outputFile, "%f %f %f ", pixelColor[0]*255.9, pixelColor[1]*255.9, pixelColor[2]*255.9);

            // reset (this is ugly ik)
            directionVar[0] = lowerLeft[0];
            directionVar[1] = lowerLeft[1];
            directionVar[2] = lowerLeft[2];
            horizontalTimesX[0] = horizontal[0];
            horizontalTimesX[1] = horizontal[1];
            horizontalTimesX[2] = horizontal[2];
            verticalTimesY[0] = vertical[0];
            verticalTimesY[1] = vertical[1];
            verticalTimesY[2] = vertical[2];
            
        }
        fprintf(outputFile, "\n");
    }


    fclose(outputFile);
    return 0;
}