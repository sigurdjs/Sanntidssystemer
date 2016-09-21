#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <dispatch/dispatch.h>

#define NTHREADS 5

void* use_resource(void* thread_number);
dispatch_semaphore_t semaphore;

int main() {

    semaphore = dispatch_semaphore_create(3);
    pthread_t threads[NTHREADS]; 
    int thread_number[] = {1,2,3,4,5};

    int err;
    for(int i = 1; i < NTHREADS; i++) {
        err= pthread_create(&threads[i], NULL, use_resource, &thread_number[i]);
        if(err) {
            fprintf(stderr, "Error: pthread_create() return code %d\n",err);
            return(-1);
        }
    }

    for(int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i],NULL);
    }

    dispatch_release(semaphore);
    
    printf("finished \n");
    return(0);
}


void* use_resource(void* thread_number){
    int number = *((int*) thread_number);
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    for(int i = 0; i < 20; i++) {
        printf("Thread number: %i has executed %i times.\n",number,i);
        usleep(100000);
    }
    dispatch_semaphore_signal(semaphore);
    return NULL;
} 
