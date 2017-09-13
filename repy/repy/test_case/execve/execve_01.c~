#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int ret;
    ret = 0;

    char *cmd[] = { "ls", "-l", (char *)0 };
    char *env[] = { "HOME=/usr/home", "LOGNAME=home", (char *)0 };

    printf("<cage 1> --beginning of program-- \n");

    ret = execve("/bin/ls", cmd, env);

    printf("<cage 1> return not expected! \n");
    printf("<cage 1> ret = %d \n", ret);

    return 0;
}
