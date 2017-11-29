#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
    
int global_var = 100;

int main (int argc, char **argv) {
    int local_var = 1;
    void *global_var_ptr;
    void *local_var_ptr;
    global_var_ptr = (void*) &global_var;
    local_var_ptr = (void*) &local_var;
    int data_size = 8;

    printf("global_var_ptr = %p, global_var = %d \n", global_var_ptr, global_var);
    printf("local_var_ptr = %p, local_var = %d \n", local_var_ptr, local_var);

    // first, try to create a shared memory region
    int shmid = shmget(IPC_PRIVATE, data_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    // attach two different memory addresses to the shared memory region
    char *reg1 = (char *) shmat (shmid,  (void*) 0x5000000, 0);
    char *reg2 = (char *) shmat (shmid,  (void*) 0x6000000, 0);
    printf("Successfully created regions at %p and %p of length %d \n", reg1, reg2, data_size);
    // initially, both addresses content no data
    printf("Initial data value: reg1[0] = %d, reg2[0] = %d \n", reg1[0], reg2[0]);
    // copying local_var data to reg1
    printf("Now copying data %d to reg1. \n", local_var);
    memcpy(reg1, local_var_ptr, data_size);
    printf("Done copying data %d to reg1. \n", local_var);
    // verify that both reg1 and reg2 have data of local_var
    printf("After writing data to reg1, reg1[0] = %d, reg2[0] = %d \n", reg1[0], reg2[0]);
    
    // copying global_var data to reg1
    printf("Now copying data %d to reg1. \n", global_var);
    memcpy(reg1, global_var_ptr, data_size);
    printf("Done copying data %d to reg1. \n", global_var);
    // verify that both reg1 and reg2 have data of global_var
    printf("After writing data to reg1, reg1[0] = %d, reg2[0] = %d \n", reg1[0], reg2[0]);
    
    return 0;
}

