#include<stdio.h>
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

    // ray direction (B) (vector) (along z axis for camera)

    // float num (t) (distance from origin?)

    // p(t) = A + t*B (p is position) (points at stuff) (might be moved outta here idk)
};

int main() {

    // these values will be parsed in later
    int sceneWidth = 200;
    int sceneHeight = 100;

    // background color
    int bgColor[3] = {80, 200, 255};
    char* outputFileName = "hello.ppm";
    FILE* outputFile;

    // open up
    outputFile = fopen(outputFileName, "w");

    // ppm header
    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", sceneWidth, sceneHeight);
    fprintf(outputFile, "%d\n", 255);

    // index vars
    int widthIndex;
    int heightIndex;

    // DRAW BACKGROUND
    for ( heightIndex = 0; heightIndex < sceneHeight; heightIndex++)
    {
        for (widthIndex = 0; widthIndex < sceneWidth; widthIndex++)
        {
            fprintf(outputFile, "%d %d %d ", bgColor[0], bgColor[1], bgColor[2]);
        }
        fprintf(outputFile, "\n");
    }


    fclose(outputFile);
    return 0;
}