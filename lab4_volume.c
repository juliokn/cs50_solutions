// Modifies the volume of an audio file
// By multiplying samples (int16_t) by a factor

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
// Number of bytes in .wav header

const int HEADER_SIZE = 44;

typedef uint8_t BYTE;
typedef int16_t SAMPLE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    
    BYTE bytes[HEADER_SIZE];

    fread(bytes, sizeof(BYTE), HEADER_SIZE, input); //copying header
    fwrite(bytes, sizeof(BYTE), HEADER_SIZE, output); //writing header

    // TODO: Read samples from input file and write updated data to output file

    SAMPLE sample; //

    while (fread(&sample, sizeof(SAMPLE), 1, input))    //a while loop to read every sample until the end of the file
    {                                               
        sample = sample * factor;                       //so there's no need to have an array to store every fread item
        fwrite(&sample, sizeof(SAMPLE), 1, output);     //it will loop until there's no more int16_t (until fread==0)
    }
    
    // Close files
    fclose(input);
    fclose(output);
}