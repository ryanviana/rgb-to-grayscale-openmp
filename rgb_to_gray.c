#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <image-file-name>\n", argv[0]);
        return 1;
    }

    double start, stop; // Variables to measure execution time

    FILE *fIn = fopen(argv[1], "rb"); // Input File name (binary read)
    if (fIn == NULL)
    {
        printf("File does not exist.\n");
        return 1;
    }

    char outputFileName[255];
    strcpy(outputFileName, argv[1]);
    strcat(outputFileName, "_grayscale.bmp"); // Append "_grayscale" to the input file name

    FILE *fOut = fopen(outputFileName, "wb"); // Output File name (binary write)

    unsigned char byte[54];
    fread(byte, sizeof(unsigned char), 54, fIn);

    int height = *(int *)&byte[18];
    int width = *(int *)&byte[22];
    int bitDepth = *(int *)&byte[28];
    int size = height * width;
    unsigned char *buffer = (unsigned char *)malloc(3 * size); // Buffer to hold RGB values

    start = omp_get_wtime(); // Measure start time

    fread(buffer, sizeof(unsigned char), 3 * size, fIn); // Read the entire image into memory

    for (int i = 0; i < size; i++)
    {
        unsigned char gray = (buffer[i * 3] * 0.3) + (buffer[i * 3 + 1] * 0.59) + (buffer[i * 3 + 2] * 0.11);
        buffer[i * 3] = gray;
        buffer[i * 3 + 1] = gray;
        buffer[i * 3 + 2] = gray;
    }

    // Write the modified data back to the output file
    fwrite(byte, sizeof(unsigned char), 54, fOut);
    fwrite(buffer, sizeof(unsigned char), 3 * size, fOut);

    stop = omp_get_wtime(); // Measure end time

    fclose(fOut);
    fclose(fIn);
    free(buffer);

    // printf("\nExecution Time: %lf milliseconds\n", (stop - start) * 1000.0);
    FILE *fTime = fopen("time.txt", "w");
    if (fTime != NULL)
    {
        fprintf(fTime, "%lf", (stop - start) * 1000.0);
        fclose(fTime);
    }
    else
    {
        printf("Failed to open time.txt for writing.\n");
    }
    return 0;
}
