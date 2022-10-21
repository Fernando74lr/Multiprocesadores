#include<stdio.h>
#include "omp.h"

int main() 
{
    FILE *f;  
    f = fopen("fer.txt", "w");
    fprintf(f, "Fernando López Ramírez.\nIngeniería en Sistemas Digitales y Robótica.");
    fclose(f);
}

/*
    EXECUTE:
    gcc -fopenmp .\create_txt_file.c
    ./a.exe

    REFERENCES:
    https://www.w3schools.blog/c-file-handling
*/