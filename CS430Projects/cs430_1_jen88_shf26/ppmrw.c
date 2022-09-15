// Project 1: PPM Format
#include <stdio.h> // fopen, fscanf and friends
#include <stdlib.h> // malloc and friends
#include <stdint.h> // standard integer types
#include <ctype.h> // isspace and friends

int readP3File(FILE *filehandle, int currentChar, int outputFlag);

// pixel type
typedef struct pixel
{
    // might be unsigned int? uint8 or something idk
    int R, G, B;
} pixel;

// USAGE

// TO CONVERT TO P3 from whatever
// ppmrw 3 input.ppm output.ppm

// TO CONVERT TO P6 from whatever
// ppmrw 6 input.ppm output.ppm


// TODO: HANDLE ERROR CODES FROM INPUT FILES
// ADD HELP FUNCTION WITH A USAGE STRING (maybe not needed)
// ADD SUPPORT FOR COMMENTS IN INPUT FILE
// fix p3 fscanf or test against other values

// This section reads in files
// P3
int readP3File(FILE *filehandle, int currentChar, int outputFlag)
{
    // variable init
    int doneFlag = 0;
    int rowColFilledFlag = 0;
    int row = 0;
    int col = 0;
    int maxColor = -1;

    // move from 3 onto data
    currentChar = fgetc(filehandle);

    // parse until row and column count reached
    while(doneFlag == 0)
    {   

        // if the character is a space or newline, parse one
        if (isspace(currentChar) != 0)
        {
            currentChar = fgetc(filehandle);
        }

        // if the character is a comment, parse until end of line
        else if (currentChar == '#')
        {
            while(currentChar != '\n')
            {
                currentChar = fgetc(filehandle);
            }

        }
        // if value is a digit, it must be a row or column (if we dont yet have a row or col)
        else if ((isdigit(currentChar) != 0) && rowColFilledFlag == 0)
        {
            if (row == 0)
            {
                // go back one so we can capture whole int
                fseek(filehandle, -1L, SEEK_CUR);

                // scan int into maxcolor var
                fscanf(filehandle, "%d", &row);
                currentChar = fgetc(filehandle);
            }
            else if(col == 0)
            {
                // go back one so we can capture whole int
                fseek(filehandle, -1L, SEEK_CUR);

                // scan int into maxcolor var
                fscanf(filehandle, "%d", &col);
                currentChar = fgetc(filehandle);
                rowColFilledFlag = 1;
            }
        }
        // otherwise we are getting the color max value
        else if ((isdigit(currentChar)) && maxColor == -1)
        {
            // go back one so we can capture whole int
            fseek(filehandle, -1L, SEEK_CUR);

            // scan int into maxcolor var
            fscanf(filehandle, "%d", &maxColor);
            currentChar = fgetc(filehandle);
        }
        // get to next int to begin storing data (maxcolor is negative 1 because maybe it can be 0?)
        else if ((isdigit(currentChar)) != 0 && maxColor > -1)
        {
            // done looping, all data parsed from header
            doneFlag = 1;

        }
        else
        {
            printf("Error: Unknown character obstructring input file\n");

            return 6;
        }
    }

    // create array in memory to store data
    pixel p3data[sizeof(pixel) * row * col];

    // go back at spot
    fseek(filehandle, -1L, SEEK_CUR);

    // Loop until end of file, filling out array with data
    int index = 0;

    // read in values
    while(!feof(filehandle) && (index) < (row*col))
    {
        // scan in data MAYBE FIX FOR COMMENTS
        int scan_count = fscanf(filehandle, "%d %d %d", &p3data[index].R, &p3data[index].G, &p3data[index].B);

        printf("index: %d\n", index);
        printf("%d\n", p3data[index].R);
        printf("%d\n", p3data[index].G);
        printf("%d\n\n", p3data[index].B);

        index+=1;

        // ADD SUPPORT FOR COMMENTS AT END OF LINES??
    }


    printf("P3 Read Complete\n");
    // now write to file
    if (outputFlag == 0)
    {
    }
    // this is an else if because error has been handled in main
    else
    {
    }

    return 0;
}


// P6
// PPM USES 24 BITS PER PIXEL so uint24 i think
int readP6File(FILE *filehandle, int currentChar, int outputFlag)
{
    // variable init
    int doneFlag = 0;
    int rowColFilledFlag = 0;
    int row = 0;
    int col = 0;
    int maxColor = -1;

    // move from 3 onto data
    currentChar = fgetc(filehandle);

    // parse until row and column count reached
    while(doneFlag == 0)
    {   
        

        // if the character is a space or newline, parse one
        if (isspace(currentChar) != 0)
        {
            currentChar = fgetc(filehandle);
        }

        // if the character is a comment, parse until end of line
        else if (currentChar == '#')
        {
            while(currentChar != '\n')
            {
                currentChar = fgetc(filehandle);
            }

        }
        // if value is a digit, it must be a row or column (if we dont yet have a row or col)
        else if ((isdigit(currentChar) != 0) && rowColFilledFlag == 0)
        {
            if (row == 0)
            {
                // go back one so we can capture whole int
                fseek(filehandle, -1L, SEEK_CUR);

                // scan int into maxcolor var
                fscanf(filehandle, "%d", &row);
                currentChar = fgetc(filehandle);

            }
            else if(col == 0)
            {
                // go back one so we can capture whole int
                fseek(filehandle, -1L, SEEK_CUR);

                // scan int into maxcolor var
                fscanf(filehandle, "%d", &col);
                currentChar = fgetc(filehandle);
                rowColFilledFlag = 1;
            }
        }
        // otherwise we are getting the color max value
        else if ((isdigit(currentChar)) && maxColor == -1)
        {
            // go back one so we can capture whole int
            fseek(filehandle, -1L, SEEK_CUR);

            // scan int into maxcolor var
            fscanf(filehandle, "%d", &maxColor);

            doneFlag = 1;
        }
        // // get to next int to begin storing data (maxcolor is negative 1 because maybe it can be 0?)
        // // DOESNT RUN
        // else if ((isdigit(currentChar)) != 0 && maxColor > -1)
        // {
        //     // done looping, all data parsed from header
        //     doneFlag = 1;

        // }
        // else
        // {
        //     doneFlag = 1;

            

        //     //return 6;
        // }
    }

    //ended after maxcolor was retrieved, currentchar is 2

    // maybe not needed
    fseek(filehandle, 1, SEEK_CUR);





        typedef struct pixelTwo
    {
    // might be unsigned int? uint8 or something idk
    unsigned char R, G, B;
    } pixelTwo;









    // create array in memory to store data
    pixelTwo p6data[sizeof(pixel) * row * col];


    // Loop until end of file, filling out array with data
    int index = 0;




    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    unsigned char currentPixel[row*col*3];

    while (index < row*col)
    {
    fread(&currentPixel[index], 3, 1, filehandle);
    
    
    index += 1;
    }

    index -= 1;
    printf("%d %d %d\n", currentPixel[index], currentPixel[index+1], currentPixel[index+2]);

    

    printf("P6 Read Complete\n");
    // now write to file
    if (outputFlag == 0)
    {
    }
    // this is an else if because error has been handled in main
    else
    {
    }

    return 0;
}

// This section writes to files

// P3 might need parameter to be a pointer idk
int writeP3File()
{
    // write data

    printf("P3 Write Complete\n");
    return 0;
}

// P6
int writeP6File()
{
    // write data

    printf("P6 Write Complete\n");
    return 0;
}


// main function
// argv[1] = output type, 2 is input file, 3 is output file
int main(int argc, char *argv[])
{
    // count arguments to make sure there is a correct number of them
    if (argc != 4)
    {
        //ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Unsupported Number of of Arguments\n");

        // return error code
        return 1;
    }

    // VARIABLES
    // 1 or 0 output bool (0 is p3, 1 is p6)
    int outputFlag;
    // character int for reading file
    int currentChar;

    // get output type
    if (argv[1][0] == '6')
    {
        // set flag to 1 because p6
        outputFlag = 1;
    }
    // otherwise, its a p3 output
    else if (argv[1][0] == '3')
    {
        // set to 0 for p3
        outputFlag = 0;
    }
    // wrong output type error
    else
    {
        //ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Unsupported Output Type\n");

        // return error code
        return 4;
    }

    // open file
    FILE *filehandle = fopen(argv[2], "r");

    // error handling if filename is incorrect
    if (!filehandle)
    {
        //ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Incorrect Input Filename\n");

        // return error code
        return 5;
    }

    // get first character (hopefully P)
    currentChar = fgetc(filehandle);

    // make sure formatted correctly with P
    if(currentChar == 'P')
    {
        // get next character (hopefully 3 or 6)
        currentChar = fgetc(filehandle);

        // if were inputting p3
        if(currentChar == '3')
        {
            // read in p3 file
            readP3File(filehandle, currentChar, outputFlag);
        }
        // otherwise its gotta be 6
        else if(currentChar == '6')
        {
            // read in p6 file
            readP6File(filehandle, currentChar, outputFlag);
        }
        else
        {
            //ERROR UNSUPPORTED FILE to stderr
            fprintf( stderr, "Error: Unsupported PPM Input File Format\n");

            // return error code
            return 2;
        }
    }
    else
    {
        // ERROR UNSUPPORTED FILE to stderr
        fprintf( stderr, "Error: Unsupported Input File\n");

        // return error code
        return 3;
    }
    
    fclose(filehandle);
    return 0;
}






