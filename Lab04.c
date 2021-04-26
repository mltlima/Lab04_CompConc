/**
 * Miguel Lima Tavares
 * 119161571
 * Lab 04
 * Atividade 4
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NTHREADS 4

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond, y_cond;

//Thread A
void *A (void *t) {

    pthread_mutex_lock(&x_mutex);

    while (x < 3) {
        pthread_cond_wait(&y_cond, &x_mutex);
    }
    printf("Volte Sempre!\n");

    pthread_mutex_unlock(&x_mutex);   
    pthread_exit(NULL);
}


//Thread B
void *B (void *t) {
    pthread_mutex_lock(&x_mutex);

    if(x < 1){
      pthread_cond_wait(&x_cond, &x_mutex);
    }
    x++;
    printf("Fique a vontade.\n");

    if (x == 3){
        pthread_cond_signal(&y_cond); 
    }
    

    pthread_mutex_unlock(&x_mutex);   
    pthread_exit(NULL);
}

//Thread C
void *C (void *t) {
    pthread_mutex_lock(&x_mutex);

    if(x < 1){
      pthread_cond_wait(&x_cond, &x_mutex);
    }

    x++;
    printf("Sente-se por favor.\n"); 

    if (x == 3){
        pthread_cond_signal(&y_cond); 
    }

    pthread_mutex_unlock(&x_mutex);  
    pthread_exit(NULL);
}

//Thread D
void *D (void *t) {
    printf("Seja bem-vido!\n"); 

    pthread_mutex_lock(&x_mutex);
    x++;
    if (x == 1){
        pthread_cond_broadcast(&x_cond);
    }
    
    pthread_mutex_unlock(&x_mutex);  
    pthread_exit(NULL);
}



//----------------------------------------
int main(void) {

    pthread_t threads[NTHREADS];

    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init(&x_cond, NULL);
    pthread_cond_init(&y_cond, NULL);

    //Threads
    pthread_create(&threads[0], NULL, A, NULL);
    pthread_create(&threads[1], NULL, B, NULL);
    pthread_create(&threads[2], NULL, C, NULL);
    pthread_create(&threads[3], NULL, D, NULL);

    /* Espera todas as threads completarem */
    for (int i = 0; i < NTHREADS; i++) {
      pthread_join(threads[i], NULL);
    }

    /* Desaloca variaveis e termina */
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond);
    return 0;

}