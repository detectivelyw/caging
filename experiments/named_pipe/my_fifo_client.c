// C program to implement one side of FIFO
// This side reads the user input, and then writes to our pipe
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
 
int main()
{
    int fd;
 
    // FIFO file path
    char * myfifo = "/tmp/myfifo";
 
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(myfifo, 0666);
 
    char str[256];
    while(1)
    {
        // Now open in write mode and write
        // string taken from user input.
        fd = open(myfifo, O_WRONLY);
        fgets(str, 256, stdin);
        write(fd, str, strlen(str)+1);
        close(fd);

        // To exit our client program, just input any string starts with '0'
        if (str[0] == '0') {
           break;
        }
    }
    return 0;
}
