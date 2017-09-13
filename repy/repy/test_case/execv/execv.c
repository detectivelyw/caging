#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int ret;
    ret = 0;
    printf("<cage 1> --beginning of program-- \n");
    char *const parmList[] = {"/bin/ls", "-l", "/u/userid/dirname", NULL};
    ret = execv("/bin/ls", parmList);

    printf("<cage 1> return not expected! \n");
    printf("<cage 1> ret = %d \n", ret);

    return 0;
}
