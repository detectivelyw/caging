#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <fcntl.h>

#define SIZE 4096

int main(void) {
  int fd = shm_open("/tmpmem", O_RDWR | O_CREAT, 0666);

  char *buf = mmap((void*) 0x5000000, SIZE, PROT_READ | PROT_WRITE,
      MAP_SHARED, fd, 0);
  buf[0] = 41;
  buf[1] = 42;

  char *buf2 = mmap((void*) 0x6000000, SIZE, PROT_READ | PROT_WRITE,
    MAP_PRIVATE, fd, 0);

  printf("buf = %p, buf2 = %p \n", buf, buf2);

  printf("buf[0]: %i, buf[1]: %i, buf2[0]: %i, buf2[1]: %i\n",
      buf[0],
      buf[1],
      buf2[0],
      buf2[1]);

  buf2[0] = 43;
  buf2[1] = 44;
  printf("buf[0]: %i, buf[1]: %i, buf2[0]: %i, buf2[1]: %i\n",
      buf[0],
      buf[1],
      buf2[0],
      buf2[1]);

  return 0;
}
