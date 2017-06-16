#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void)
{
   int linux_pipe_capacity = 16*4096;
   int data_transfer = 1024*1024*100;
   char readbuffer[16*4096];

   int fd = 8000;
   int ret = -1;
   int string_size = 200;
  
   int i; 
   int test_rounds = data_transfer/string_size;
   clock_t begin = clock();
   for (i = 1; i <= test_rounds; i++) {
       if(read(fd, readbuffer, string_size) < 0) {
           write(2, "An error occurred in the read!\n", 31);
       }
       // printf("<cage 02> %s \n", readbuffer);
       // printf("<cage 02> Read pipe successfully! %i \n", i);
   }
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("<cage 02> time = %f \n", time_spent);
   printf("<cage 02> program finished! \n");
   return(0); 
}
