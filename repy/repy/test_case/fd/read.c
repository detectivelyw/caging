#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
 
int main(void)
{
    int filedesc = open("./test_case/files/testfile01.txt", O_RDONLY);

    printf("fd = %i \n", filedesc);
 
    if (filedesc < 0) {
        printf("Couldn't open file!\n");
        return -1;
    }

    char data[128];
 
    if(read(filedesc, data, 128) < 0) {
        write(2, "An error occurred in the read!\n", 31);
    }

    printf("%s \n", data);
    printf("Read file successfully!\n");
 
    return 0;
}
