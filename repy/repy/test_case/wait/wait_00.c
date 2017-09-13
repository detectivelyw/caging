#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid = getpid();
    pid_t val;
    int status;

    val = wait(&status);
    printf("Current process id number is: %d \n", pid);
    printf("val = %d; status = %d \n", val, status);

    return 0;
}
