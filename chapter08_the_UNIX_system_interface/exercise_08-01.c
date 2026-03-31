// Exercise 8.1
// Rewrite the program cat from Chapter 7 (7.5) using read, write,
// open and close instead of their standard library equivalents.
// Perform experiments to determine the relative speeds of the two 
// versions.

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 1024

/* cat: concatenate files, version 1 */
int main(int argc, char *argv[]){
  int fd;
  void filecopy(int from, int to);

  if(argc == 1) /* no args; copy standard input */
    filecopy(0, 1);
  else
    while(--argc > 0)
      if((fd = open(*++argv, O_RDONLY)) == -1){
        fprintf(stderr, "cat: can't open %s\n", *argv);
        return 1;
      }
      else {
        filecopy(fd, 1);
        close(fd);
      }

  return 0;
}

/* filecopy: copy file ifp to file ofp */
void filecopy(int from, int to){
  char buf[BUFSIZE];
  int n;

  while((n = read(from, buf, BUFSIZE)) > 0)
    write(to, buf, n);
}
