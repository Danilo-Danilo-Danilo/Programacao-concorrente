#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main() {
    int num_steps = 100000000;
    double step;
    int i;
    double x, piS, piP, sum = 0.0;
    int threads = omp_get_num_threads();
    printf("Threads:%d", threads);

    double tempoInicialSequencial = omp_get_wtime();
    step = 1.0/(double) num_steps;
    for (i = 0; i < num_steps; i++){
        x = (i + 0.5) * step;
        sum = sum + 4.0/ (1.0 + x*x);
     }

     piS = step * sum;
     double tempoFinalSequencial = omp_get_wtime();

     double tempoInicialParalelo = omp_get_wtime(); // tempo inicial
     sum = 0.0;
    #pragma omp parallel private (x) num_threads(4)

    {
        #pragma omp for reduction (+:sum)
            for (i = 0; i < num_steps; i++){
                x = (i + 0.5) * step;
                sum = sum + 4.0/ (1.0 + x*x);
            }
    }
    piP = step * sum;
    double tempoFinalParalelo = omp_get_wtime();
     printf("Sequencial\n:");
     printf("%.5f\n",piS);
     double tempoSequencial = tempoFinalSequencial-tempoInicialSequencial;
    printf("Tempo sequencial: %lf\n",tempoSequencial);
     printf("--------------------------\n");
    printf("Paralelo:\n:");
     printf("%.5f\n",piP);
     double tempoParalelo = tempoFinalParalelo-tempoInicialParalelo;
    printf("Tempo paralelo: %.4f\n",tempoParalelo);
    printf("--------------------------\n");
    double speedup = tempoSequencial/tempoParalelo;
     printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/4.0;
    printf("Eficiência: %f\n",eficiencia);
    return 0;
}