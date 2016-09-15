#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* increment_and_print(void* thread_number);

int global_variable = 0;
pthread_t thread1, thread2;
int thread_number1 = 1;
int thread_number2 = 2;

int main() {
    int err1 = pthread_create(&thread1, NULL, increment_and_print, &thread_number1);
    if(err1) {
        fprintf(stderr, "Error: pthread_create() return code %d\n",err1);
        return(-1);
    }
    int err2= pthread_create(&thread2, NULL, increment_and_print, &thread_number2);
    if(err2) {
        fprintf(stderr, "Error: pthread_create() return code %d\n",err2);
        return(-1);
    }
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return(0);
}


void* increment_and_print(void* thread_number){
    int number = *((int*) thread_number);
    int local_variable = 0;
    for(int i = 0; i < 10; i++) {
        printf("Thread number: %i, Global value: %i, Local value: %i\n",number,global_variable,local_variable);
        local_variable++;
        global_variable++;
    }
    return NULL;
} 
