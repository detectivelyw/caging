#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(void)
{
   int i; 
   int linux_pipe_capacity = 16*4096;
   int data_transfer = 1024*1024*100;
   int fd[2];
   int ret; 
   int string_size = 200;
   char string[] = "0123456789";

   int totoal_data_size; 
   totoal_data_size = 10 * 6553+1;
   char *total_data = malloc(totoal_data_size);

   if (total_data != NULL)
   { 
       strcpy(total_data, string);
       for (i = 0; i < 6552; i++) {
           strcat(total_data, string);
       }
   }
   
   fd[0] = 0;
   fd[1] = 1;

   ret = -1;
   ret = pipe(fd);
        
   // printf("<cage 01> ret: %i \n", ret);
   // printf("<cage 01> fd[0]: %i \n", fd[0]);
   // printf("<cage 01> fd[1]: %i \n", fd[1]);

   int test_rounds = data_transfer/string_size;
   clock_t begin = clock();
   for (i = 1; i <= test_rounds; i++) {
       write(fd[1], total_data, string_size);
       // printf("<cage 01> Write pipe successfully! %i \n", i);
   }
   clock_t end = clock();
   double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
   printf("<cage 01> time = %f \n", time_spent);
   printf("<cage 01> program finished! \n");
   return(0);
}
