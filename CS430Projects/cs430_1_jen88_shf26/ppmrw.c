// Project 1: PPM Format
#include <stdio.h> // fopen, fscanf and friends
#include <stdlib.h> // malloc and friends
#include <stdint.h> // standard integer types
#include <ctype.h> // isspace and friends

int readP3File(FILE *filehandle, int currentChar, int outputFlag);
int readP6File(FILE *filehandle, int currentChar, int outputFlag);
int writeP3File();
int writeP6File();

// USAGE

// TO CONVERT TO P3 from whatever
// ppmrw 3 input.ppm output.ppm

// TO CONVERT TO P6 from whatever
// ppmrw 6 input.ppm output.ppm

// TODO: HANDLE ERROR CODES FROM INPUT FILES
// ADD SUPPORT FOR COMMENTS IN INPUT FILE (p3 data)
// check if at end of find once we read in all the values for the while loops
// check against max colo

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
        else if ((isdigit(currentChar)) != 0 && maxColor == -1)
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
            printf("Error: Unknown character obstructing input file\n");

            return 6;
        }
    }

    // create array in memory to store data
    unsigned int p3data[row*col][3];

    // go back at spot
    fseek(filehandle, -1L, SEEK_CUR);

    // Loop until end of file, filling out array with data
    int index = 0;

    // variable creation before loop
    char charBuffer = ' ';
    int comments = 0;
    unsigned int temp;

    // read in values
    while(index < row*col && !feof(filehandle))
    {
        if ( index >= row*col )
        {
            printf("Error: Corrupted file inputted\n");

            return 11;
        }
        // check for comments
        comments = fscanf(filehandle, "%c", &charBuffer);
        
        if ( charBuffer == '#' )
        {
            while(charBuffer != '\n')
            {
                charBuffer = fgetc(filehandle);
            }
            charBuffer = fgetc(filehandle);
            
        }
        // move back one, even if comment found to ensure in correct spot for next numbers
        fseek(filehandle, -1L, SEEK_CUR);

        // scan in first number
        fscanf(filehandle, "%d", &p3data[index][0]);

        if (p3data[index][0] < 0 || p3data[index][0] > 255)
        {
            printf("Error: pixel values out of range\n");
            return 10;
        }

        printf("%d ", p3data[index][0]);

        comments = fscanf(filehandle, "%c", &charBuffer);
        
        if ( charBuffer == '#' )
        {
            //printf("HERE:%c ", charBuffer);
            while(charBuffer != '\n')
            {
                printf("%c!", charBuffer);
                charBuffer = fgetc(filehandle);
            }
            charBuffer = fgetc(filehandle);
            
        }
        // move back one, even if comment found to ensure in correct spot for next numbers
        fseek(filehandle, -1L, SEEK_CUR);


        // scan in next number
        fscanf(filehandle, "%d", &p3data[index][1]);
        if (p3data[index][1] < 0 || p3data[index][1] > 255)
        {
            printf("Error: pixel values out of range\n");
            return 10;
        }

        printf("%d ", p3data[index][1]);

        comments = fscanf(filehandle, "%c", &charBuffer);

        if ( charBuffer == '#' )
        {
            //printf("HERE:%c ", charBuffer);
            while(charBuffer != '\n')
            {
                
                charBuffer = fgetc(filehandle);
            }
            charBuffer = fgetc(filehandle);
        }
        // move back one, even if comment found to ensure in correct spot for next numbers
        fseek(filehandle, -1L, SEEK_CUR);


        // scan in next number
        fscanf(filehandle, "%d", &p3data[index][2]);
        if (p3data[index][2] < 0 || p3data[index][2] > 255)
        {
            printf("Error: pixel values out of range\n");
            return 10;
        }
        printf("%d \n\n", p3data[index][2]);

        comments = fscanf(filehandle, "%c", &charBuffer);
        if ( charBuffer == '#' )
        {
            
            while(charBuffer != '\n')
            {
                
                charBuffer = fgetc(filehandle);
            }
            charBuffer = fgetc(filehandle);

        }
        // move back one, even if comment found to ensure in correct spot for next numbers

        index+=1;
    }

    // if not enough data or too much
    if (index != row*col)
    {
        printf("Error: Corrupted File Inputted");
        return 20;
    }

    // print read message
    printf("P3 Read Complete\n");

    // now write to file
    if (outputFlag == 0)
    {
        // now write
        writeP3File();
    }
    // this is an else if because error has been handled in main
    else
    {
        // write now
        writeP6File();
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

            // all done after we get the color. Now we can parse the data
            doneFlag = 1;
        }
    }

    // move ahead one to parse data now
    fseek(filehandle, 1, SEEK_CUR);

    // Loop until end of file, filling out array with data
    int index = 0;

    // create array of data to store pixels in. (three contiguous values make up a pixel in the array)
    unsigned char p6data[row*col][3];

    // loop through data to fill array
    while (index < row*col)
    {
        // read in p6 data
        fread(&p6data[index], 3, 1, filehandle);
        
        // printf("%d ", p6data[index][0]);
        // printf("%d ", p6data[index][1]);
        // printf("%d\n", p6data[index][2]);
        
        // increment index
        index += 1;

    }

    
    // print read message
    printf("P6 Read Complete\n");

    // now write to file
    if (outputFlag == 0)
    {
        // write data now
        writeP3File();
    }
    // this is an else if because error has been handled in main
    else
    {
        // write data now
        writeP6File();
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






