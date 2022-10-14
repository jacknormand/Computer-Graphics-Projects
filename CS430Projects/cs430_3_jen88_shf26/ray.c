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
            float position[3];
            float radius;
            float color[3];
        }sphere;

        struct plane
        {
            float position[3];
            float normal[3];
            float color[3];
        }plane;
        
    }properties;

}object;


int main();
void getColor(float* dst, ray inputRay, object sceneObjects[]);
float intersectObj(object* objectShotAt, ray inputRay);


float intersectObj(object* objectShotAt, ray inputRay)
{
    if (objectShotAt->kind == SPHERE)
        {
            // SPHERE: bt^2 * b + 2tb * (A-C) + (A-C) . (A-C) - r^2 = 0
            // solve for t^2 roots
            float originCenter[] = {0,0,0};

            // solves equation above
            v3_subtract(originCenter, inputRay.origin, objectShotAt->properties.sphere.position);
            float directionDot = v3_dot_product(inputRay.direction, inputRay.direction);
            float twoTimesDot = 2.0 * v3_dot_product(originCenter, inputRay.direction);
            float radiusSq = objectShotAt->properties.sphere.radius * objectShotAt->properties.sphere.radius;
            float dotOCMinusRSquared = v3_dot_product(originCenter, originCenter) - radiusSq;
            float result = (twoTimesDot * twoTimesDot) - (4 * directionDot * dotOCMinusRSquared);
            
            return result;
        }

    return 0;

}

void getColor(float* dst, ray inputRay, object sceneObjects[])
{
    // // intersection
    // if(intersectObj(OBJECT, inputRay) > 0)
    // {
    //     dst[0] = sphereCol[0];
    //     dst[1] = sphereCol[1];
    //     dst[2] = sphereCol[2];
    //     return;
    // }
    
    float nearestTVal = 1e+9;
    float newTVal = -1;
    float pixelColor[] = {0,0,0};
    object *currentObj;

    currentObj = &sceneObjects[1];
    printf("%d", currentObj->kind);

    // loop through objects
    for (int objectIndex = 0; objectIndex < 128; objectIndex++)
    {
        currentObj = &sceneObjects[objectIndex];
        if (currentObj->kind == SPHERE)
        {
            // get new tVal from current obj
            newTVal = intersectObj(currentObj, inputRay);

            // maybe just greater than
            if (newTVal >= 0 && newTVal < nearestTVal)
            {
                nearestTVal = newTVal;
                pixelColor[0] = currentObj->properties.sphere.color[0];
                pixelColor[1] = currentObj->properties.sphere.color[1];
                pixelColor[2] = currentObj->properties.sphere.color[2];
            }

        }
        else if (currentObj->kind == PLANE)
        {
        }
        else
        {
            //printf("brrr planeOTHER\n");
        }
    }

    dst[0] = pixelColor[0];
    dst[1] = pixelColor[1];
    dst[2] = pixelColor[2];

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
    object sceneObjects[128];

    // EXAMPLE: FILLED THIS HOW IT SHOULD BE FILLED FROM INPUT (so i can test with it)
    // camera doesnt have properties because it will be read in and width and height will be set instantly
    object tempCamera;
    tempCamera.kind = CAMERA;

    object redSphere;
    float colorRedTest[] = {1,0,0};
    float positionoftestsphere[] = {0,0,-10};
    float radiusTest = .5;
    redSphere.kind = SPHERE;
    redSphere.properties.sphere.color[0] = colorRedTest[0];
    redSphere.properties.sphere.color[1] = colorRedTest[1];
    redSphere.properties.sphere.color[2] = colorRedTest[2];
    redSphere.properties.sphere.position[0] = positionoftestsphere[0];
    redSphere.properties.sphere.position[1] = positionoftestsphere[1];
    redSphere.properties.sphere.position[2] = positionoftestsphere[2];
    redSphere.properties.sphere.radius = radiusTest;

    object testPlane;
    float colorBlueTest[] = {0,0,1};
    float positionoftestplane[] = {0,0,0};
    float normalTest[] = {0,1,0};
    testPlane.kind = PLANE;
    testPlane.properties.plane.color[0] = colorBlueTest[0];
    testPlane.properties.plane.color[1] = colorBlueTest[1];
    testPlane.properties.plane.color[2] = colorBlueTest[2];
    testPlane.properties.plane.position[0] = positionoftestplane[0];
    testPlane.properties.plane.position[1] = positionoftestplane[1];
    testPlane.properties.plane.position[2] = positionoftestplane[2];
    testPlane.properties.plane.normal[0] = normalTest[0];
    testPlane.properties.plane.normal[1] = normalTest[1];
    testPlane.properties.plane.normal[2] = normalTest[2];

    // input read for test
    sceneObjects[0] = tempCamera;
    sceneObjects[1] = redSphere;
    sceneObjects[2] = testPlane;















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
            getColor(pixelColor, currentRay, sceneObjects); 
            
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