#include <stdio.h>
#include <stdlib.h>


void allocate(int value) {
    int *ptr = NULL;
    ptr = malloc(1024*1024*sizeof(char));
    *ptr = value;
    printf("test of allocated memory: %i\n",*ptr);
}


int main() {
    while(1) {
        allocate(5);
    }
    return 0;
}

