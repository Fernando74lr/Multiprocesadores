#include<stdio.h>
static long num_pasos = 1000000; // (500000) Definimos número de pasos.

double paso;

int main() 
{
    int i;
    double x, pi, sum = 0.0; // Definimos constantes.
    paso = 1.0 / num_pasos; // Definimos el paso a evaluar.

    for (i = 0; i < num_pasos; i++)
    {
        x = (i + 0.5) * paso; // Definimos el punto a evalar en función.
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = paso * sum; // Multiplicamos por la constante;
    printf("pi = (%lf)\n", pi); // Imprimimos resultado.
}

/*
    EXECUTE:
    gcc -fopenmp .\area_bajo_la_curva.c
    ./a.exe
*/