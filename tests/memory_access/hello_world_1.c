#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    int cage2_a_new = 96;
    int* cage2_a_ptr_known = (int*)0xfffefe54;

    printf("<cage 1> Hello World! 01\n");
   
    sleep(10); // we wait for cage2 to finish writing to its own memory, and then we can start the attemp to write cage2's memory.
    memcpy(cage2_a_ptr_known, (void*)(&cage2_a_new), 4);
    printf("<cage 1> a = %i \n", *cage2_a_ptr_known);
    printf("<cage 1> a_ptr = %p \n", cage2_a_ptr_known);

    return 0;
}
