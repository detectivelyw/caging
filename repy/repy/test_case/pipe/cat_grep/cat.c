/* Taken from the K&R C book */

#include <stdio.h>
#include <stdlib.h>

/* cat:  concatenate files, version 2 */
int main(int argc, char *argv[])
{
  FILE *fp;
  void filecopy(FILE *, FILE *);
  char *prog = argv[0];  /* program name for errors */

  int fd[2];
  int ret; 

  int fd_pipe_write = 8001;

  ret = -1;
  ret = pipe(fd);

  printf("<cage 01> ret: %i \n", ret);
  printf("<cage 01> fd[0]: %i \n", fd[0]);
  printf("<cage 01> fd[1]: %i \n", fd[1]);

  ret = dup2(fd_pipe_write, 1);
  
  if (argc == 1 ) /* no args; copy standard input */
    filecopy(stdin, stdout);
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
	fprintf(stderr, "%s: can't open %s\n",
		prog, *argv);
	exit(1);
      } else {
	filecopy(fp, stdout);
	fclose(fp);
      }
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing stdout\n", prog);
    exit(2);
  }
  exit(0);
  return 0;
}

/* filecopy:  copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
  int c;
  
  while ((c = getc(ifp)) != EOF)
    putc(c, ofp);
}
