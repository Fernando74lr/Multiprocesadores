#include <stdio.h>
#include <omp.h>
static long num_pasos = 500 * 1000000; // (1,000,000,000) Definimos número de pasos.
double paso;
#define NUM_THREADS 20

void main() 
{
    int i, nthreads;
    double pi, sum[NUM_THREADS], t1, t2, tiempo; // Definimos constantes.
    paso = 1.0 / num_pasos; // Definimos el paso a evaluar.

    omp_set_num_threads(NUM_THREADS);

    const double startTime = omp_get_wtime();
    t1 = omp_get_wtime();

    #pragma omp parallel
    {
        int i, id, nthrds;
        double x;
        
        id = omp_get_thread_num();
        // Capturar la etiqueta del thread que está entrando en esa sección del código
        nthrds = omp_get_num_threads();

        if (id == 0) nthreads = nthrds;

        for (i=id, sum[id]=0.0 ; i < num_pasos; i=i+nthrds)
        {
            x = (i + 0.5) * paso; // Definimos el punto a evalar en función.
            sum[id] += 4.0 / (1.0 + x*x);
        }

        printf("\nID Thread [%d]  |  Value [%f]\n", id, sum[id]);
    }

    for (i=0, pi = 0.0; i < nthreads; i++)
    {
        pi += sum[i]*paso;
    }

    t2 = omp_get_wtime();
    tiempo = t2 - t1;
    
    printf("NUM_THREADS = (%d)\n", NUM_THREADS);
    printf("num pasos = (%ld)\n", num_pasos);
    printf("pi = (%lf)\n", pi);
    printf("tomo (%lf) segundos\n\n", tiempo);
}

/*
    EXECUTE:
    gcc -fopenmp .\area_bajo_la_curva_threads.c
    ./a.exe


    Speed up = (tiempo sin mejoras) / (tiempo con mejoras)

    Prog. Pi_Parallel
    # Threads = 
    # RAM = 
    # Núcleos =
    # Frecuencia =
    Tiempo =
*/
