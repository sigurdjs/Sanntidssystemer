#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <dispatch/dispatch.h>

#define NFORKS 5
#define NPHILOSOPHERS 5

void* think_or_eat(void* philosopher_number);
int init_philosophers(pthread_t philosophers[NPHILOSOPHERS]);
void join_philosophers(pthread_t philosophers[NPHILOSOPHERS]); 
int init_forks();
void destroy_forks(); 

pthread_mutex_t forks[NFORKS];
dispatch_semaphore_t semaphore;
int running = 1;

int main() {

    semaphore = dispatch_semaphore_create(NFORKS-1);
    pthread_t phils[NPHILOSOPHERS];

    if(init_forks() != 0) {
        printf("Mutex init failed \n");
        return(-1);
    }

    init_philosophers(phils);

    printf("Press any key to exit \n");
    getchar();
    running = 0;
    printf("Exiting\n");

    join_philosophers(phils);
    destroy_forks();
    dispatch_release(semaphore);

    return(0);
}

int init_forks() {
    for(int i = 0; i < NFORKS; i++) {
        if(pthread_mutex_init(&forks[i],NULL) != 0) {
            return(-1);
        }
    }
    return(0);
}

void destroy_forks() {
    for(int i = 0; i < NFORKS; i++) {
        pthread_mutex_destroy(&forks[i]); 
    }  
}

int init_philosophers(pthread_t philosophers[NPHILOSOPHERS]) {
    int err;
    for(int i = 0; i < NPHILOSOPHERS; i++) {
        err = pthread_create(&philosophers[i],NULL,think_or_eat,(void *) (intptr_t) i);
        if(err) {
            fprintf(stderr,"Error: pthread_create() return code %d\n",err);
            return(-1);
        }
    }
    return(0);
}

void join_philosophers(pthread_t philosophers[NPHILOSOPHERS]) {
    for(int i = 0; i < NPHILOSOPHERS; i++) {
        pthread_join(philosophers[i],NULL);
    }
}

void* think_or_eat(void* philosopher_number) {
    int number = (intptr_t) philosopher_number;
    while(running) {
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
        pthread_mutex_lock(&forks[number]);
        if(number == 0) {
            pthread_mutex_lock(&forks[NFORKS-1]);
        } else {
            pthread_mutex_lock(&forks[number-1]);
        }  
        usleep(100000);
        printf("Philosopher number: %i is eating\n",number);
        sleep(1);
        pthread_mutex_unlock(&forks[number]);
        if(number == 0) {
            pthread_mutex_unlock(&forks[NFORKS-1]);
        } else {
            pthread_mutex_unlock(&forks[number-1]);
        }
        dispatch_semaphore_signal(semaphore);
        printf("Philosopher number: %i is thinking\n",number);
    }
    return NULL;
}

