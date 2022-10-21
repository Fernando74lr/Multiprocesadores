// Include libraries
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// Define number of threads
#define NUM_THREADS 2

int main()
{
    // Set num of threads
    omp_set_num_threads(NUM_THREADS);

    // Declare pointers for image & new image
    FILE *image, *outputImage;

    // Open original image
    image = fopen("original_kitten.bmp", "rb");
    // Create new image
    outputImage = fopen("kitten_red.bmp", "wb");

    // Declare width & height of the image
    long width;
    long height;
    // Declare RGB pixel chars
    unsigned char r, g, b;
    // Array for the first 54 header's line
    unsigned char xx[54];

    // Read first 54 header's line and move img memory counter
    for (int i = 0; i < 54; i++) {
        // Get header line from original img
        xx[i] = fgetc(image);
        // Set header line to new img
        fputc(xx[i], outputImage);
    }

    // Calculate the width & height of the original image
    height = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18] + 1;
    width = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22] + 1;

    // Print width & height
    printf("Img Width: %ld px\n", width);
    printf("Img Height: %ld px\n", height);
    
    // Calculate image size
    long imageSize = height * width;

    // Print image size
    printf("Image size: %ld px\n", imageSize);

    // Measure initial time (t1)
    const double startTime = omp_get_wtime();
    double t1 = omp_get_wtime();

    // Define pointers of malloc
    unsigned char* arrImgInput = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    unsigned char* arrImgOutput = (unsigned char*)malloc(2782080*sizeof(unsigned char));
    
    // Start process with parallelism
    #pragma omp parallel for
        for (int j = 0; j < imageSize; j++) {
            // Get RGB values as received: B, G, R
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);

            // Set new gray pixel to the new img with order: B, G, R
            fputc(0, outputImage);
            fputc(0, outputImage);
            fputc(r, outputImage); // In this case is just Red
        }

    // Measure final time (t2)
    double t2 = omp_get_wtime();

    // Calculate final time
    double finalTime = t2 - t1;

    // Print number of threads
    printf("Threads: %d\n", NUM_THREADS);
    // Print how much time did it take
    printf("It took (%lf) seconds\n", finalTime);

    // Close original image
    fclose(image);
    // Close new image
    fclose(outputImage);

    // End program execution
    return 0;
}

/*
    MALLOC:
    // Moving through malloc
    for (int j = 0; j < imageSize ; j++) {
        m[i] = *(p + i)
    }
*/

/*
    EXECUTE:
    gcc -fopenmp .\Actividad_2_1.c
    .\a.exe
*/

/*
    TASKS:
    + Gray scale.
    + Parallelism using "pragma for".
    / Use of malloc to calculate width & height and to flip image.
    - Horizontal flip (ask option with scanf)
    - Vertical flip (ask option with scanf)
*/