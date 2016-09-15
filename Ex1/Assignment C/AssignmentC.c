#include <stdio.h>
#include <stdlib.h>


int allocate(int value) {
    int *ptr = NULL;
    ptr = (int*)malloc(10024*10024*sizeof(char));
    if (ptr== NULL) {
        perror("Error: ");
        return(-1);
    }
    *ptr = value;
    printf("test of allocated memory: %i\n",*ptr);
    return 0;
}


int main() {
    int err = 1;
    while(1) {
        err = allocate(5);
        if (err == -1) {
            break;
        }
    }
    return 0;
}

