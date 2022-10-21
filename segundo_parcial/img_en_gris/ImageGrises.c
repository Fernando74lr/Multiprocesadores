#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
// Define number of threads
#define NUM_THREADS 10


struct my_pixel {
    unsigned char r, g, b;
};

int main()
{

    // Set num of threads
    omp_set_num_threads(NUM_THREADS);

    FILE *image, *outputImage, *lecturas;
    image = fopen("original_kitten.bmp", "rb");          //Imagen original a transformar
    outputImage = fopen("gray_kitten_img/kitten_gray.bmp", "wb");    //Imagen transformada
    long alto, ancho;

    unsigned char r, g, b;
    unsigned char xx[54];

    /* 54 because are the default lines of pure description about the img */
    // for(int i=0; i<54; i++) fputc(fgetc(image), outputImage); // Copy header to new img

    for (int i = 0; i < 54; i++)
    {
        xx[i] = fgetc(image);
        fputc(xx[i], outputImage);
    }

    ancho = (long)xx[20]*65536 + (long)xx[19]*256 + (long)xx[18];
    alto = (long)xx[24]*65536 + (long)xx[23]*256 + (long)xx[22];
    
    long n = ancho * alto * 3;

    // printf("%ld", n);
        
    // Until it isn't the end of the file
    #pragma omp parallel for
        for (long i = 0; i < n; i++)
        {
            // while(!feof(image))
            b = fgetc(image);
            g = fgetc(image);
            r = fgetc(image);

            unsigned char pixel = 0.21*r+0.72*g+0.07*b;

            // Built new img
            fputc(b, outputImage);
            fputc(g, outputImage);
            fputc(r, outputImage);
            // printf("Ahi vamos");
        }   

    fclose(image);
    fclose(outputImage);
    return 0;
}

/*
    EXECUTE:
    gcc -fopenmp .\ImageGrises.c
    ./a.exe
*/

// poner imagen en arreglo o malloc y voltearlo al final