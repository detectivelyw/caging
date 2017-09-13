#include <stdio.h>
#include <unistd.h>

int test_global = 98;

int main(int argc, char **argv)
{
    printf("--beginning of program-- \n");

    printf("&test_global = %p \n", &test_global);
    printf("test_global = %i \n", test_global);

    int test_local = 99;
    printf("&test_local = %p \n", &test_local);
    printf("test_local = %i \n", test_local);

    int counter = 0;
    pid_t pid = fork();

    if (pid == 0) {
        // child process
        int i;
        for (i = 0; i < 5; i++) {
            printf("[child process %d]: counter = %d \n", pid, ++counter);
        }
    }
    else if (pid > 0) {
        // parent process
        int j;
        for (j = 0; j < 5; j++) {
            printf("[parent process %d]: counter = %d \n", pid, ++counter);
        }
    }
    else {
        // fork failed
        printf("fork() failed! \n");
        return 1;
    }

    if (pid == 0) {
        printf("[child process %d]: --end of program-- \n", pid);
    }
    else {
        printf("[parent process %d]: --end of program-- \n", pid);
    }

    return 0;
}
