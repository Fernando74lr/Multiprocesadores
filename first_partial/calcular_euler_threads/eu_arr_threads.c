#include <stdio.h>
#include <omp.h>
#include <math.h>

// Define number of threads
#define NUM_THREADS 6
// Step number
#define N 2500000 // 2,500,00 steps

// Define file pointer
FILE *fptr;

// Function declarations
void iteration(int op_type);

// Define global variables
static double w0 = 0.5, a = 0, b = 2;
static double h, t[N], w[N], ab;
// Iterator
int i, id;

int main() {
    // Set number of threads
    omp_set_num_threads(NUM_THREADS);

    // Open new file
    fptr=fopen("Euler_n_0.txt","w");

    // Prints
    printf("\nNumero de pasos: %d \n", N);
    fprintf(fptr, "Datos que encuentra el metodo de Euler (variable ind.\t variable dep.\t numero de thread).\n");

    // Define variables
    double t1, t2, f_time; // Time measurement

    // Measure initial time (t1)
    const double startTime = omp_get_wtime();
    t1 = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
                (void)iteration(1);
        }
    }

    // Measure final time (t2)
    t2 = omp_get_wtime();

    // Calculate final time
    f_time = t2 - t1;

    // Write in file (Hard Drive)
    for(i=0; i<N; i++)
    {
        fprintf(fptr, "%f\t %f\n", t[i], w[i]);
    }

    // Close file
    fclose(fptr);

    // Print time
    printf("tomo (%lf) segundos\n", f_time);
}

// @N: number of steps
// @op_type: type of operation (exp, pow, sin, cos, etc.)
void iteration(int op_type) {
    id = omp_get_thread_num();
    printf("ID Thread [%d]\n", id);
    // fprintf(fptr, "%f\t\n", a);
    h = (b-a) / N;
    w[0] = w0;
    t[0] = a;
    
    // Calculate and store in bidimensional arrays t[calculus]
    // Stored in RAM
    for(i=0; i<N; i++) 
    {
        t[i] = a + (h*i);
        switch (op_type)
        {
            case 1: // "exp"
                w[i] = exp2((w[i-1]+h)*(1+t[i-1]*(t[i-1]-w[i-1])));
                // printf("w[%d][%f]\n", id, w[i]);
                break;
            case 2: // "pow"
                w[i] = w[i-1]+h*(1+t[i-1]*pow(t[i-1]-w[i-1], 2));
                break;
            case 3: // "sin"
                w[i] = sin(w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]));
                break;
            case 4: // "cos"
                w[i] = cos(w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]));
                break;
            case 5: // "sqrt"
                w[i] = sqrt(w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]));
                break;
            case 6: // "sinh"
                w[i] = sinh(w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]));
                break;
            case 7: // "cosh"
                w[i] = cosh(w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]));
                break;
            default:
                w[i]=w[i-1]+h*(1+t[i-1]*t[i-1]-w[i-1]);
                break;
        }
    }
}

/*
   EXECUTE:
   gcc -fopenmp .\eu_arr_threads.c
   ./a.exe
*/

// velocidad ram
// agregar threads a este código
// num pasos: 2.5 M

// Numero de pasos:2500000 Atendido por thread:1
// tomo (18.303000) segundos