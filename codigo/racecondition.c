#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10000000
#define N_THREADS 4

int *V;
long long total = 0;

void *soma_trecho(void *arg) {
    long tid = (long) arg;
    long ini = tid * (N / N_THREADS);
    long fim = (tid + 1) * (N / N_THREADS);
    for (long i = ini; i < fim; i++)
        total += V[i]; // <<< CONDICAO DE CORRIDA
    return NULL;
}



int main(void){

    V = malloc(N*sizeof(int));
    pthread_t threads[N_THREADS]; // array de threads
    for (int i=0; i<N;i++) {
        V[i]=10;
    }

    for(long t=0; t<N_THREADS;t++){
        pthread_create(&threads[t],NULL, soma_trecho, (void*)t);
    }

    for(long t=0; t<N_THREADS;t++){
        pthread_join(threads[t], NULL);   // sem & antes de threads[t]
    }

    printf("soma esperada:%lld\n",(long long)N*10);
    printf("soma calculada:%lld\n",total);






}