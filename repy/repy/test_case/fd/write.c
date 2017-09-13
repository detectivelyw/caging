#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
 
int main(void)
{
    int filedesc = open("./test_case/files/testfile01.txt", O_WRONLY | O_APPEND);

    printf("fd = %i \n", filedesc);
 
    if (filedesc < 0) {
        printf("Couldn't open file!\n");
        return -1;
    }
 
    if (write(filedesc, "This will be output to testfile.txt\n", 36) != 36) {
        write(2, "There was an error writing to testfile.txt\n", 43);
        printf("Write file failed!\n");
        return -1;
    }

    printf("Write file successfully!\n");
 
    return 0;
}
