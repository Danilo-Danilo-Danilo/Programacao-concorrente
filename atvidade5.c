
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define TAMANHO 100000000

double *gerar_vetor(int n);
int *gerar_vetor_inteiro(int n);
void mostrar_vetor_inteiro(int *v,int tamanho);
void mostrar_vetor(double *v,int tamanho);

int main() {
    /*
    INICIO
    */
    time_t t;
    double tempoInicialSequencial,tempoFinalSequencial;
    double tempoInicialParalelo, tempoFinalParalelo;
    srand(time(NULL));
    int *vetor = NULL;
    vetor = gerar_vetor_inteiro(TAMANHO);
    int n, i;
    printf("Informe o numero:");
    scanf("%d", &n);
    int countS = 0;
    int countP = 0;
    tempoInicialSequencial = omp_get_wtime(); 
    for (i=0;i<TAMANHO;i++) {
        if(vetor[i] == n){
            countS++;
        }
        
    }
    tempoFinalSequencial = omp_get_wtime();

    // em paralelo
    countP = 0;
    tempoInicialParalelo = omp_get_wtime(); // tempo inicial
    #pragma omp parallel num_threads(3)
    {
        #pragma omp for reduction (+:countP)
            for (i=0;i<TAMANHO;i++) {
                if(vetor[i] == n){
                    countP++;
                }
            }
    }
    tempoFinalParalelo = omp_get_wtime();
    printf("Sequencial :\n");
    printf("Contagem: %d\n",countS);
    double tempoSequencial = tempoFinalSequencial-tempoInicialSequencial;
    printf("Tempo sequencial: %lf\n",tempoSequencial);
    printf("--------------------------\n");


    printf("Paralelo:\n");
    printf("Contagem: %d\n",countP);
    double tempoParalelo = tempoFinalParalelo-tempoInicialParalelo;
    printf("Tempo paralelo: %.4f\n",tempoParalelo);
    double speedup = tempoSequencial/tempoParalelo;
    printf("--------------------------\n");
    printf("Speedup: %f\n",speedup);
    double eficiencia = speedup/3.0;
    printf("Eficiência: %f\n",eficiencia);
    return 0;
    /*
    FIM
    */
}

double *gerar_vetor(int n) {
    double *vetor;
    int i;
    vetor = (double *)malloc(sizeof(double) * n);
    for (i=0;i<n;i++) {
        double num = (rand() / (float)RAND_MAX);
        vetor[i] = num;
    }
    return vetor;
}

int *gerar_vetor_inteiro(int n) {
    int *vetor;
    int i;
    vetor = (int *)malloc(sizeof(int) * n);
    for (i=0;i<n;i++) {
        int num = (rand() % MAX);
        vetor[i] = num;
    }
    return vetor;
}

void mostrar_vetor(double *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%.5f]",v[i]);
    }
    printf("\n");
}

void mostrar_vetor_inteiro(int *v,int tamanho) {
    int i;
    for (i=0;i<tamanho;i++) {
        printf("[%d]",v[i]);
    }
    printf("\n");
}