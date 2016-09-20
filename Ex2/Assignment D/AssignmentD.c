#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* write_variables(void*);
void* print_variables(void*);

int var1 = 0;
int var2 = 0;
int running = 1;
pthread_mutex_t lock;



int main() {

    if(pthread_mutex_init(&lock,NULL) != 0) {
        printf("Init mutex failed \n");
        return(-1);
    }

    pthread_t thread1, thread2;
    int err1 = pthread_create(&thread1, NULL, write_variables, NULL);
    if(err1) {
        fprintf(stderr,"Error: pthread_create() return code %d\n",err1);
        return(-1);
    }
    int err2 = pthread_create(&thread2, NULL, print_variables, NULL);
    if(err2) {
        fprintf(stderr,"Error: pthread_create() return code %d\n",err1);
        return(-1);
    }
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_mutex_destroy(&lock);
    return(0);
}

void* write_variables(void* dummy) {
    while(running) {
        pthread_mutex_lock(&lock);
        var1++;
        var2 = var1;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* print_variables(void* dummy) {
    for(int i = 0; i < 20; i++) {
        printf("Variable 1 has value: %i, variable 2 has value: %i\n", var1,var2);
        usleep(100000);
    }
    running = 0;
    return NULL;
}




