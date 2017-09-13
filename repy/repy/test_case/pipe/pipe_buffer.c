#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

struct fifo_buffer {
     char* buf;
     int head;
     int tail;
     int size;
};

// This initializes the FIFO structure with the given buffer and size
void fifo_init(struct fifo_buffer* f, char* buf, int size){
     f->head = 0;
     f->tail = 0;
     f->size = size;
     f->buf = buf;
}

// This reads n chars from the FIFO
// The number of chars read is returned
int fifo_read(struct fifo_buffer* f, void* buf, int n){
     int i;
     char* p;
     p = buf;
     for(i = 0; i < n; i++){
          if(f->tail != f->head){ // see if any data is available
               *p++ = f->buf[f->tail];  // grab a char from the buffer
               f->tail++;  // increment the tail
               if(f->tail == f->size){  // check for wrap-around
                    f->tail = 0;
               }
          } else {
               return i; // number of chars read
          }
     }
     return n;
}

// This writes up to n chars to the FIFO
// If the head runs in to the tail, not all chars are written
// The number of chars written is returned
int fifo_write(struct fifo_buffer* f, const void* buf, int n){
     int i;
     const char* p;
     p = buf;
     for(i = 0; i < n; i++){
           // first check to see if there is space in the buffer
           if((f->head + 1 == f->tail) ||
                ((f->head + 1 == f->size) && (f->tail == 0))){
                 return i; // no more room
           } else {
               f->buf[f->head] = *p++;
               f->head++;  // increment the head
               if(f->head == f->size){  // check for wrap-around
                    f->head = 0;
               }
           }
     }
     return n;
}
 
pthread_t tid[2];
struct fifo_buffer buffer; 
char buf[10];
int size = 10;
int n = 0;

void* doSomeThing(void* arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("[Thread 01 start] \n");
        char string[7] = "AaaBbb\0";
        n = 7;
        int ret = 0;
        ret = fifo_write(&buffer, string, n);
        printf("[Thread 01] ret = %i \n", ret);
        printf("[Thread 01] %s \n", string);
    }

    else
    {
        printf("[Thread 02 start] \n");
        n = 7;
        int ret = 0;
        while (!ret) {
            sleep(2);
            ret = fifo_read(&buffer, buf, n);            
        }
        printf("[Thread 02] ret = %i \n", ret);
        printf("[Thread 02] %s \n", buf);
    }
    return NULL;
}

int main()
{
    fifo_init(&buffer, buf, size);

    int i = 0;
    int err;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\n Can't create thread :[%s]", strerror(err));
        else {
            printf("\n Thread created successfully\n");
        } 
        i++;
    }
    
    sleep(5);
    return 0;
}
