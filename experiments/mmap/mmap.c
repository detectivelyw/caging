#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
    
int main (int argc, char **argv) {
    int shmid = shmget(IPC_PRIVATE, 0x1000*10, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    char *reg1 = (char *) shmat (shmid,  (void*) 0x5000000, 0);
    char *reg2 = (char *) shmat (shmid,  (void*) 0x6000000, 0);
    printf("Successfully created regions at %p and %p of length %#x\n",
            reg1, reg2, 0x1000*10);
    reg1[0] = 'X';
    printf("After writing 'X' to reg1[0], reg2[0] = '%c'\n", reg2[0]);
    printf("Trying to write to reg2[0] (should succeed)\n");
    printf("Changing protections of reg2 with mprotect...\n");
    mprotect(reg2, 0x1000*10, PROT_READ);                                                                                      
    printf("Trying to write to reg2[0] (should crash)\n");
    reg2[0] = 'Y';
    return 0;
}

/* Output:
Successfully created regions at 0x5000000 and 0x6000000 of length 0xa000
After writing 'X' to reg1[0], reg2[0] = 'X'
Trying to write to reg2[0] (should succeed)
Changing protections of reg2 with mprotect...
Trying to write to reg2[0] (should crash)
Segmentation fault (core dumped)
*/
