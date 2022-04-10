#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* global variable */
volatile pthread_mutex_t mutex;
int g_count = 0;

void func(){
    
    int i;
    for(i = 0; i < 10; i++){
        /* critical section */
        pthread_mutex_lock((pthread_mutex_t*)&mutex);
        g_count++;
        printf("ID:%d, g_count:%d\n", pthread_self(), g_count);
        pthread_mutex_unlock((pthread_mutex_t*)&mutex);
    }
    
    printf("ID:%d, finished.\n", pthread_self());
}

int main(int argc, char *argv[]){
    pthread_t thd1, thd2;
    
    if(pthread_mutex_init((pthread_mutex_t*)&mutex, NULL)){
        printf("mutex create failed.\n");
        exit(1);
    }
    
    pthread_create(&thd1, NULL, (void*)func, NULL);
    pthread_create(&thd2, NULL, (void*)func, NULL);
    
    pthread_join(thd1, NULL);
    pthread_join(thd2, NULL);
    
    pthread_mutex_destroy((pthread_mutex_t*)&mutex);
    
    return 0;
}
