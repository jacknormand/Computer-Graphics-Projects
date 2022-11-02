// Project 1: PPM Format
#include <stdio.h> // fopen, fscanf and friends
#include <stdlib.h> // malloc and friends
#include <stdint.h> // standard integer types
#include <ctype.h> // isspace and friends

int readP3File(FILE *filehandle, int currentChar, int outputFlag, char* outputFileName);
int readP6File(FILE *filehandle, int currentChar, int outputFlag, char* outputFileName);
int writeP3ToP3File(int row, int col, unsigned int p3data[row*col][3], int maxColor, char* outputFileName);
int writeP6ToP6File(int row, int col, unsigned char p6data[row*col][3], int maxColor, char* outputFileName);
int writeP6ToP3File(int row, int col, unsigned char p6data[row*col][3], int maxColor, char* outputFileName);
int writeP3ToP6File(int row, int col, unsigned int p6data[row*col][3], int maxColor, char* outputFileName);

// USAGE

// TO CONVERT TO P3 from whatever
// ppmrw 3 input.ppm output.ppm

// TO CONVERT TO P6 from whatever
// ppmrw 6 input.ppm output.ppm

// This section reads in files
// P3
int readP3File(FILE *filehandle, int currentChar, int outputFlag, char* outputFileName)
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
            fprintf( stderr, "Error: Unknown character obstructing input file\n");

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
            fprintf( stderr, "Error: Corrupted file inputted\n");

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
            fprintf( stderr, "Error: pixel values out of range\n");
            return 10;
        }

        //printf("%d ", p3data[index][0]);

        comments = fscanf(filehandle, "%c", &charBuffer);
        
        if ( charBuffer == '#' )
        {
            //printf("HERE:%c ", charBuffer);
            while(charBuffer != '\n')
            {
                //printf("%c!", charBuffer);
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
            fprintf( stderr, "Error: pixel values out of range\n");
            return 10;
        }

        //printf("%d ", p3data[index][1]);

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


        // scan in next number
        fscanf(filehandle, "%d", &p3data[index][2]);
        if (p3data[index][2] < 0 || p3data[index][2] > 255)
        {
            fprintf( stderr, "Error: pixel values out of range\n");
            return 10;
        }
        //printf("%d \n\n", p3data[index][2]);

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
        fprintf( stderr, "Error: Corrupted File Inputted");
        return 20;
    }

    // print read message
    printf("P3 Read Complete\n");

    // now write to file
    if (outputFlag == 0)
    {
        // now write
        writeP3ToP3File(row, col, p3data, maxColor, outputFileName);
    }
    // this is an else if because error has been handled in main
    else
    {
        // write now
        writeP3ToP6File(row, col, p3data, maxColor, outputFileName);
    }

    return 0;
}


// P6
int readP6File(FILE *filehandle, int currentChar, int outputFlag, char* outputFileName)
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

        else
        {
            fprintf( stderr, "Error: Unknown character obstructing input file\n");

            return 6;
        }
        
    }

    // move ahead one to parse data now
    fseek(filehandle, 1, SEEK_CUR);

    // Loop until end of file, filling out array with data
    int index = 0;

    // create array of data to store pixels in. (three contiguous values make up a pixel in the array)
    unsigned char p6data[row*col][3];

    // loop through data to fill array
    // && !feof(filehandle)
    while (index < row*col)
    {
        // read in p6 data
        fread(&p6data[index], 1, 3, filehandle);
        
        //uncomment to view
        printf("%d ", p6data[index][0]);
        printf("%d ", p6data[index][1]);
        printf("%d\n", p6data[index][2]);
        
        // increment index
        index += 1;

    }

    // print read message
    printf("P6 Read Complete\n");

    // now write to file
    if (outputFlag == 0)
    {
        // write data now
        // 
        writeP6ToP3File(row, col, p6data, maxColor, outputFileName);
    }
    // this is an else if because error has been handled in main
    else
    {
        // write data now
        writeP6ToP6File(row, col, p6data, maxColor, outputFileName);
    }

    return 0;
}

// This section writes to files
// P3 might need parameter to be a pointer idk
int writeP3ToP3File(int row, int col, unsigned int p3data[row*col][3], int maxColor, char* outputFileName)
{
    // create and open the output file
    FILE* outputFile;
    outputFile = fopen(outputFileName, "w");

    // write the file type, the rows and columns, and maxColor
    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", row, col);
    fprintf(outputFile, "%d\n", maxColor);

    // initialize loop variables
    int pixelIndex;
    int pixelDataIndex;

    // loop until every pixel is accessed
    for (pixelIndex = 0; pixelIndex < row*col; pixelIndex++)
    {
        // check column width for newline spacing
        if (pixelIndex % col == 0 && pixelIndex != 0)
        {
            fprintf(outputFile, "\n");
        }
        // loop and print out each pixel's rgb
        for (pixelDataIndex = 0; pixelDataIndex < 3; pixelDataIndex++)
        {
            fprintf(outputFile, "%4d", p3data[pixelIndex][pixelDataIndex]);
        }
    }

    fclose(outputFile);

    printf("P3 Write Complete\n");
    return 0;
}

int writeP6ToP3File(int row, int col, unsigned char p6data[row*col][3], int maxColor, char* outputFileName)
{
    // create and open the output file
    FILE* outputFile;
    outputFile = fopen(outputFileName, "w");

    // write the file type, the rows and columns, and maxColor
    fprintf(outputFile, "P3\n");
    fprintf(outputFile, "%d %d\n", row, col);
    fprintf(outputFile, "%d\n", maxColor);

    // initialize loop variables
    int pixelIndex, pixelDataIndex;

    // loop until every pixel is accessed
    for (pixelIndex = 0; pixelIndex < row*col; pixelIndex++)
    {
        // check column width for newline spacing
        if (pixelIndex % row == 0 && pixelIndex != 0)
        {
            fprintf(outputFile, "\n");
        }
        // loop and print out each pixel's rgb
        for (pixelDataIndex = 0; pixelDataIndex < 3; pixelDataIndex++)
        {
            fprintf(outputFile, "%4d", p6data[pixelIndex][pixelDataIndex]);
        }
    }

    fclose(outputFile);

    printf("P3 Write Complete\n");
    return 0;
}

// P6
int writeP6ToP6File(int row, int col, unsigned char p6data[row*col][3], int maxColor, char* outputFileName)
{
    // create and open the output file
    FILE* outputFile;
    outputFile = fopen(outputFileName, "w");

    // write the file type, the rows and columns, and maxColor
    fprintf(outputFile, "P6\n");
    fprintf(outputFile, "%d %d\n", row, col);
    fprintf(outputFile, "%d\n", maxColor);

    // initialize loop variables
    int pixelIndex, pixelDataIndex;

    // loop until every pixel is accessed
    for (pixelIndex = 0; pixelIndex < row*col; pixelIndex++)
    {
        // loop and print out each pixel's rgb
        for (pixelDataIndex = 0; pixelDataIndex < 3; pixelDataIndex++)
        {
            fprintf(outputFile, "%c", p6data[pixelIndex][pixelDataIndex]);
        }
    }
    fclose(outputFile);

    printf("P6 Write Complete\n");
    return 0;
}

int writeP3ToP6File(int row, int col, unsigned int p6data[row*col][3], int maxColor, char* outputFileName)
{
    // create and open the output file
    FILE* outputFile;
    outputFile = fopen(outputFileName, "w");

    // write the file type, the rows and columns, and maxColor
    fprintf(outputFile, "P6\n");
    fprintf(outputFile, "%d %d\n", row, col);
    fprintf(outputFile, "%d\n", maxColor);

    // initialize loop variables
    int pixelIndex, pixelDataIndex;

    // loop until every pixel is accessed
    for (pixelIndex = 0; pixelIndex < row*col; pixelIndex++)
    {
        // loop and print out each pixel's rgb
        for (pixelDataIndex = 0; pixelDataIndex < 3; pixelDataIndex++)
        {
            fprintf(outputFile, "%c", (char)p6data[pixelIndex][pixelDataIndex]);
        }
    }
    fclose(outputFile);

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

    // return code
    int returnCode = 0;

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

    // TODO: Error handling for output file name
    char* outputFileName = argv[3];

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
            returnCode = readP3File(filehandle, currentChar, outputFlag, outputFileName);

        }
        // otherwise its gotta be 6
        else if(currentChar == '6')
        {
            // read in p6 file
            returnCode = readP6File(filehandle, currentChar, outputFlag, outputFileName);
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
    return returnCode;
}






