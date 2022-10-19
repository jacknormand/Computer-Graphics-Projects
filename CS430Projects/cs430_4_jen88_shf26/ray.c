#include<stdio.h>
#include<string.h>
#include "v3math.h"

#define NULLOBJ 100
#define CAMERA 200
#define SPHERE 300
#define PLANE 400

// TODO: change attributes and add new ones
// add shadows


// this doesnt even need to be a struct cus were only using one ray over and over lol
typedef struct ray
{
    // ray origin (A) (vector) (0,0,0 for camera)
    float* origin;

    // ray direction (B) (vector) (along z axis for camera)
    float* direction;

}ray;

// the everything struct
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

        // direction dot product with intputray direction
        float directionDot = v3_dot_product(inputRay.direction, inputRay.direction);

        // times 2 by origincenter and direction 
        float twoTimesDot = 2.0 * v3_dot_product(originCenter, inputRay.direction);

        // square radius 
        float radiusSq = objectShotAt->properties.sphere.radius * objectShotAt->properties.sphere.radius;

        // subtract r^2
        float dotOCMinusRSquared = v3_dot_product(originCenter, originCenter) - radiusSq;

        // set result 
        float result = (twoTimesDot * twoTimesDot) - (4 * directionDot * dotOCMinusRSquared);
        
        // if positive result, return 
        if (result >= 0)
        {
            // do some math and return
            float partOne = (-twoTimesDot - sqrt(result));

            return partOne / (2.0*directionDot);
        }
        else
        {
            // otherwise its negative, just return a negative value so we know
            return -1.0;
        }
        return result;
    }
    // gotta be a plane
    else if (objectShotAt->kind == PLANE)
    {
        //t = -(AX0 + BY0 + CZ0 + D) / (AXd + BYd + CZd)
        float distanceFromPlane[] = {0,0,0};

        //Pn times ray direction
        float Vd = v3_dot_product(objectShotAt->properties.plane.normal, inputRay.direction);
        
        // if 0 then paralell to ray, back out
        // NOTE: if one sided planes, stop if vd>0
        if(Vd == 0 )
        {
            // no intersect
            return -1.0;
        }
        // if >0, normal is pointing away. we assume one sided planes for now
        else if (Vd > 0)
        {
            return -1.0;
        }

        v3_subtract(distanceFromPlane, objectShotAt->properties.plane.position, inputRay.origin);

        float vZero = v3_dot_product(distanceFromPlane, objectShotAt->properties.plane.normal);

        float resultONE = vZero/Vd;

        // if less than one, its intersecting behind camera so back out
        if (resultONE < 0)
        {
            return -1.0;
        }

        // otherwise return ray intersection 
        return resultONE;
        
    }

    return 0;

}

void getColor(float* dst, ray inputRay, object sceneObjects[])
{
    // variable initialization

    // lets hope no t value is greater than this lol
    float nearestTVal = 1e+9;
    float newTVal = -1;
    float pixelColor[] = {0,0,0};
    object* currentObj;
    int objectIndex;
    // loop through objects
    for ( objectIndex = 0; objectIndex < 128; objectIndex++)
    {
        // get object
        currentObj = &sceneObjects[objectIndex];

        if (currentObj->kind == SPHERE)
        {
            // get new tVal from current obj
            newTVal = intersectObj(currentObj, inputRay);

            // get nearest
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
            newTVal = intersectObj(currentObj, inputRay);

            // intersects behind origin not of interest
            if (newTVal >= 0 && newTVal < nearestTVal)
            {
                nearestTVal = newTVal;
                pixelColor[0] = currentObj->properties.plane.color[0];
                pixelColor[1] = currentObj->properties.plane.color[1];
                pixelColor[2] = currentObj->properties.plane.color[2];
            }
        }
    // otherwise doesnt fit plane or sphere, skip
    }

    // set pixel
    dst[0] = pixelColor[0];
    dst[1] = pixelColor[1];
    dst[2] = pixelColor[2];

}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        //ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Unsupported number of arguments\n");

        // input error
        return 1;
    }

    // parse in data
    FILE* filehandle = fopen(argv[3], "r");

    if (!filehandle)
    {
        // print
        fprintf(stderr, "Error: Wrong input file\n");

        // input error
        return 1;
    }

    // get first line
    char currentLine[2048];
    float recoveredNum = 0.0;
    int objIndex = 0;
    float cameraWidth = 0;
    float cameraHeight = 0;
    object sceneObjects[128];

    // loop through lines
    while(fgets(currentLine, 2048, filehandle) && objIndex < 128)
    {
        char* word = strtok(currentLine, ",");

        // if camera
        if (strcmp(word, "camera") == 0)
        {
            object newObj;
            newObj.kind = CAMERA;

            // loop wild word isnt null
            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    if (strcmp(word, "width") == 0)
                    {
                        // get width
                        recoveredNum = atof(strtok(NULL, ","));
                        cameraWidth = recoveredNum;

                    }
                    else if (strcmp(word, "height") == 0)
                    {
                        // get height
                        recoveredNum = atof(strtok(NULL, ","));
                        cameraHeight = recoveredNum;
                    }
                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }

        else if (strcmp(word, "sphere") == 0)
        {
            object newObj;
            newObj.kind = SPHERE;

            // defaults
            newObj.properties.sphere.color[0] = 0;
            newObj.properties.sphere.color[1] = 0;
            newObj.properties.sphere.color[2] = 0;

            newObj.properties.sphere.position[0] = 0;
            newObj.properties.sphere.position[1] = 0;
            newObj.properties.sphere.position[2] = 0;

            newObj.properties.sphere.radius = 0;


            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    if (strcmp(word, "color") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.color[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.color[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.sphere.color[2] = recoveredNum;
                    }
                    else if (strcmp(word, "position") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.position[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.position[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));
                        if (recoveredNum > 0)
                        {
                            printf("Warning: A sphere z coordinate is positive. Changing to negative...\n");
                            recoveredNum *= -1;
                        }
                        newObj.properties.sphere.position[2] = recoveredNum;
                    }
                    else if (strcmp(word, "radius") == 0)
                    {
                        // get radius
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.sphere.radius = recoveredNum;
                    }
                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }

        else if (strcmp(word, "plane") == 0)
        {
            object newObj;
            newObj.kind = PLANE;

            newObj.properties.plane.color[0] = 0;
            newObj.properties.plane.color[1] = 0;
            newObj.properties.plane.color[2] = 0;

            newObj.properties.plane.position[0] = 0;
            newObj.properties.plane.position[1] = 0;
            newObj.properties.plane.position[2] = 0;

            newObj.properties.plane.normal[0] = 0;
            newObj.properties.plane.normal[1] = 0;
            newObj.properties.plane.normal[2] = 0;

            while(word)
            {
                // get next word
                word = strtok(NULL, ": ");

                // if word isnt null
                if(word)
                {
                    if (strcmp(word, "color") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");
                        // get Red
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.color[0] = recoveredNum;

                        // get Blue
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.color[1] = recoveredNum;

                        // get Green
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.plane.color[2] = recoveredNum;
                    }
                    else if (strcmp(word, "position") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.position[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.position[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.plane.position[2] = recoveredNum;
                    }
                    else if (strcmp(word, "normal") == 0)
                    {
                        // get left brace
                        word = strtok(NULL, "[");

                        // get X
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.normal[0] = recoveredNum;

                        // get Y
                        recoveredNum = atof(strtok(NULL, ","));
                        newObj.properties.plane.normal[1] = recoveredNum;

                        // get Z
                        recoveredNum = atof(strtok(NULL, "]"));
                        newObj.properties.plane.normal[2] = recoveredNum;
                    }
                }

            }

            // set to new object
            sceneObjects[objIndex] = newObj;
            objIndex++;
        }
        else
        {
            printf("Error: Invalid input object\n");
            return 20;
        }
    }

    fclose(filehandle);
    //done parsing

    // read in width height
    int sceneWidth = atoi(argv[1]);
    int sceneHeight = atoi(argv[2]);

    // if aspect ratio of scene and camera dont line up, give warning
    if (sceneWidth/sceneHeight != (int)(cameraWidth/cameraHeight))
    {
        printf("Warning: Aspect ratio of scene and camera do not match. Picture may look screwed up\n");
    }

    // focal length always 1, same with origin always 0,0,0
    float focalLength = 1;
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