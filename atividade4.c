#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main() {

    int i = 0;
    int n;
    double *vetor = NULL;
    double somaS = 0;
    double somaP = 0;
    double tempoInicialSequencial,tempoFinalSequencial;
    double tempoInicialParalelo, tempoFinalParalelo;

    do{
        printf("Informe o numero:");
        scanf("%d", &n);
    }while(n<100000000);

    // em sequência
    tempoInicialSequencial = omp_get_wtime(); 
    for (i=1;i <= n ;i++) {
        if(n % i == 0){
            somaS = somaS + i;
        }
        
    }
    tempoFinalSequencial = omp_get_wtime();
    

    // em paralelo

    tempoInicialParalelo = omp_get_wtime(); // tempo inicial
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:somaP)
            for (i = 1 ;i <= n; i++) {
                if(n % i == 0){
                    somaP = somaP + i;
        }
            }
    }

    tempoFinalParalelo = omp_get_wtime();
    double mediaP = somaP/(double)n;
    


    double mediaS = somaS/(double)n;
    printf("Sequencial :\n");
    printf("Soma: %lf\n",somaS);
    printf("Media: %lf\n",mediaS);
    double tempoSequencial = tempoFinalSequencial-tempoInicialSequencial;
    printf("Tempo sequencial: %lf\n",tempoSequencial);
    printf("--------------------------\n");


    printf("Paralelo:\n");
    printf("Soma: %lf\n",somaP);
    printf("Media: %lf\n",mediaP);
    double tempoParalelo = tempoFinalParalelo-tempoInicialParalelo;
    printf("Tempo paralelo: %.4f\n",tempoParalelo);
    double speedup = tempoSequencial/tempoParalelo;
    printf("--------------------------\n");
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Eficiência: %f\n",eficiencia);
    return 0;
}