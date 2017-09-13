#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
void *x, *y;

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
        printf("x=%p\n", x);
        printf("*x=%d\n", *(int*)(x));
        printf("y=%p\n", y);
        printf("*y=%d\n", *(int*)(y));
    }
    else
    {
        printf("\n Second thread processing\n");
        printf("x=%p\n", x);
        printf("*x=%d\n", *(int*)(x));
        printf("y=%p\n", y);
        printf("*y=%d\n", *(int*)(y));
    }

    for(i=0; i<(0xFFFFFFFF);i++);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;
    x = malloc(4);
    y = malloc(4);
    *(int *)(y) = 99;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\n Can't create thread :[%s]", strerror(err));
        else {
            printf("\n Thread created successfully\n");
            *(int *)(x) = i+1;
            printf("x=%p\n", x);
            printf("*x=%d\n", *(int*)(x));
        } 
        i++;
    }

    sleep(5);
    return 0;
}
