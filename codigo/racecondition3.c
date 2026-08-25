#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

#define N 1000000

int main(){
    long long total=0;
    int *vetor = malloc(N*sizeof(int));
    for(int i=0;i<N;i++)
        vetor[i]=10;
    
    double inicio = omp_get_wtime(); // tempo para ver quanto demorou
    omp_set_num_threads(1);

    #pragma omp parallel for reduction(+:total) //incia uma area que sera paralelizada de acordo com o numero de threads
    for (long i=0;i<N;i++){
        total += vetor[i]; // <<< CONDICAO DE CORRIDA
    }
    double fim = omp_get_wtime();
    printf("soma esperada:%lld\n",(long long)N*10);
    printf("soma calculada:%lld\n",total);
    printf("tempo gasto:%lf\n",fim-inicio);
    free(vetor);
    return 0;
    //para  compilar gcc -fopenmp racecondition3.c -o racecondition3; qual o comando
    //no codespace eu instalo gcc como? sudo apt update
    //sudo apt install build-essential
    //./racecondition3
    //htop para monitorar o uso de CPU
    //rodar em loop while true; do ./racecondition3; done

}