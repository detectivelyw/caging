#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
    int cage2_a = 99;
    int* cage2_a_ptr = &cage2_a;
    int* cage2_a_ptr_known = (int*)0xfffefe54;
    int cage2_a_new_1 = 98;
    int cage2_a_new_2 = 97;
    
    printf("<cage 2> Hello World! 02\n");
    printf("<cage 2> a = %i \n", cage2_a);
    printf("<cage 2> a_ptr = %p \n", cage2_a_ptr);
   
    memcpy(cage2_a_ptr, (void*)(&cage2_a_new_1), 4);
    printf("<cage 2> a = %i \n", cage2_a);
    printf("<cage 2> a_ptr = %p \n", cage2_a_ptr);
    
    memcpy(cage2_a_ptr_known, (void*)(&cage2_a_new_2), 4);
    printf("<cage 2> a = %i \n", cage2_a);
    printf("<cage 2> a_ptr = %p \n", cage2_a_ptr_known);

    sleep(30); // we wait to make sure that cage1 has finished its attemp to write the memory in cage2, and then see if it succeeded. 
    printf("<cage 2> a = %i \n", cage2_a);
    printf("<cage 2> a_ptr = %p \n", cage2_a_ptr);

    return 0;
}
