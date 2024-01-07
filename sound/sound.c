#include <stdio.h>
#include <stdint.h> // to create and customize an int variable(chose the number of bits and the type(signed or unsigned)) 
#include <stdlib.h> // to use atof so that I can convert the command line argument to a floating point factor

const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    float factor;
    //the  buffer should contain one sample at a time it has to be an unsigned int (for reasons i dont know) ana it's 2byte large
    int16_t buffer;
    //an array to store the header file that we'll copy from the original file to the new file:
    uint8_t header[HEADER_SIZE];
    //check if the number of arguments is correct:
    if(argc != 4)
    {
        printf("format: ./sound input.wav output.wav\n");
        return 1;
    }
    //opening the input file in read mode:
    FILE *input = fopen(argv[1], "rb");
    //check if it is entered correctly:
    if (input == NULL)
    {
        printf("could not open file\n");
        return 1;
    }
    //opening output file in write mode
    FILE *output = fopen(argv[2],"wb");
    // check if it is entered correctly:
    if (output == NULL)
    {
        printf("could not open file\n");
        return 1;
    }
    //copy the file's header from the input file to the output file:
    fread(header, HEADER_SIZE, 1,input);//the fread function will read from the input file "HEADER_SIZE"*1 bytes in the header(which is an array of 44 bytes)
    fwrite(header, HEADER_SIZE,1,output);//the fwrite function will write "HEADER_SIZE"*1 bytes from the header to the output file 
    //reading the factor from the command line arguments:
    factor= atof(argv[3]);
    //the program will execute if the factor isnt entered properly
    if (0>factor || factor>10)
    {
        printf("0<=factor<=10");
        return 1;
    }
    //copying the original file samples , multiplying them by the factor and writing them into the output file;
    while(fread(&buffer, sizeof(int16_t), 1, input)!=0)//fread will return 0 if it did not read any sample and the loop will end there
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    //closing the files
    fclose(input);
    fclose(output);
}