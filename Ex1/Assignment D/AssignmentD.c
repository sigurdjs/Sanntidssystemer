#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/times.h>
#include <unistd.h>

void* print_message(void* ptr);
void busy_wait_delay(int seconds);

pthread_t thread1, thread2;
const char* message1 = "This is thread 1\n";
const char* message2 = "This is thread 2\n";


int main() {

    int err1 = pthread_create(&thread1, NULL, print_message, (void*) message1);
    if(err1) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n",err1);
        return(-1);
    }
    int err2 = pthread_create(&thread2, NULL, print_message, (void*) message2);
    if(err2) {
        fprintf(stderr, "Error - pthread_create() return code: %d\n",err2);
        return(-1);
    }
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    return(0);
}

void* print_message(void* ptr) {
    char* message;
    message = (char*) ptr;
    printf("%s \n", message);
    busy_wait_delay(5);
//    sleep(5);
    printf("%s \n", message);
    return ptr;
}

void busy_wait_delay(int seconds)
{
	int i, dummy;
	int tps = sysconf(_SC_CLK_TCK);
	clock_t start;
	struct tms exec_time;
    times(&exec_time);
    start = exec_time.tms_utime;
    while((int) (exec_time.tms_utime - start) < (seconds * tps)) {
        for(i=0; i<1000; i++) {
            dummy = i;
        }
        times(&exec_time);
    }
}


