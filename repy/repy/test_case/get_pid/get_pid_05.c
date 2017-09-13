#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    pid_t pid = getpid();
    fprintf(stdout, "Current process id number is: %d \n", pid);

    return 0;
}
