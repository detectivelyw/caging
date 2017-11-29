#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *shared = mmap((void*) 0x5000000, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    int *shared_02 = mmap((void*) 0x5000000, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0); 
    *shared = 1;
    // *shared_02 = 2;
    printf("%p \n", shared);
    printf("%d \n", *shared);
    printf("%p \n", shared_02);
    printf("%d \n", *shared_02);
}
