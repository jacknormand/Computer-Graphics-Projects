#include<stdio.h>
#include "v3math.h"

#define NULLOBJ 100
#define CAMERA 200
#define SPHERE 300
#define PLANE 400

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

typedef struct object
{
    // 100 = not object
    // 200 = camera
    // 300 = sphere
    // 400 = plane
    int kind;

    union properties
    {
        struct sphere
        {
            float* position;
            float radius;
            float* color;
        }sphere;

        struct plane
        {
            float* position;
            float* normal;
            float* color;
        }plane;
        
    }properties;

}object;



int main();
void getColor(float* dst, ray inputRay);
float intersectObj(object objectShotAt, ray inputRay);


float intersectObj(object objectShotAt, ray inputRay)
{
    if (objectShotAt.kind == SPHERE)
        {
            // SPHERE: bt^2 * b + 2tb * (A-C) + (A-C) . (A-C) - r^2 = 0
            // solve for t^2 roots
            float originCenter[] = {0,0,0};

            // solves equation above
            v3_subtract(originCenter, inputRay.origin, objectShotAt.properties.sphere.position);
            float directionDot = v3_dot_product(inputRay.direction, inputRay.direction);
            float twoTimesDot = 2.0 * v3_dot_product(originCenter, inputRay.direction);
            float radiusSq = objectShotAt.properties.sphere.radius * objectShotAt.properties.sphere.radius;
            float dotOCMinusRSquared = v3_dot_product(originCenter, originCenter) - radiusSq;
            float result = (twoTimesDot * twoTimesDot) - (4 * directionDot * dotOCMinusRSquared);
            
            // hit if >0
            if ( result > 0 )
            {
                return 1;
            }
            // other didnt hit
            else
            {
                return -1;
            }
        }

    

}

void getColor(float* dst, ray inputRay)
{
    // make object TEMp
    object redSphere;
    float spherePos[] = {0, 0,-15};
    float sphereCol[] = {1,0,0};

    redSphere.properties.sphere.position = spherePos;
    redSphere.properties.sphere.radius = 2;
    redSphere.properties.sphere.color = sphereCol;
    redSphere.kind = SPHERE;



    // intersection
    if(intersectObj(redSphere, inputRay) > 0)
    {
        dst[0] = sphereCol[0];
        dst[1] = sphereCol[1];
        dst[2] = sphereCol[2];
        return;
    }

    dst[0] = 0;
    dst[1] = 0;
    dst[2] = 0;

    // // nomralize direction
    // float normalized[] = {0,0,0};
    // // set colors
    // float colorWhite[] = {1.0,1.0,1.0};
    // float colorRed[] = {0.5,0.7,1};
    // v3_normalize(normalized, inputRay.direction);

    // // get it done
    // float lenT = .5 * (normalized[1] + 1.0);
    // float neglenT = 1 - lenT;
    // v3_scale(colorWhite, neglenT);
    // v3_scale(colorRed, lenT);
    // v3_add(dst, colorRed, colorWhite);

}



int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        //ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Unsupported Number of of Arguments\n");

        // input error
        return 1;
    }

    // read in width height
    int sceneWidth = atoi(argv[1]);
    int sceneHeight = atoi(argv[2]);

    //  @HENRY PARSE INFO IN HERE FROM FILE 
    // dont need to set any values i can do that later just parse into the object list

    // list of objects youll fill
    object Obejcts[128];
















    // camera info also parsed from file
    float cameraWidth = .5;
    float cameraHeight = .5;
    // focal length always 1, same with origin always 0,0,0
    float focalLength = 1.0;
    float origin[] = {0,0,0};
    // horizontal and vertical floats to traverse view
    float horizontal[] = {cameraWidth, 0, 0};
    float vertical[] = {0, cameraHeight, 0};

    //CALCULATIONS
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

    char* outputFileName = argv[4];
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
    // pixel that gets written out
    float pixelColor[] = {0,0,0};

    // ray
    ray currentRay;
    currentRay.origin = origin;

    //printf("1:%f\n", pixelColor[0]);
    //printf("2:%f\n", pixelColor[1]);
    //printf("3:%f\n", pixelColor[2]);

    // iterate over pixels in image, one a time,  shooting a ray 
    // through the center of the pixel out into the scene, 
    // looking for intersections between each ray and the scene geometry.
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