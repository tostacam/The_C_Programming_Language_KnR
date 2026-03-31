// 8.2 Low Level I/O-Read and Write

#include "syscalls.h"
#include <unistd.h>

int getchar1(void), getchar2(void);

/* copy input to output */
int main(){
  char buf[BUFSIZ];
  int n;

  while((n = read(0, buf, BUFSIZ)) > 0)
    write(1, buf, n);
  
  return 0;
}

/* getchar: unbuffered single character input */
int getchar1(void){
  char c;

  return (read(0, &c, 1) == 1) ? (unsigned char)c : EOF;
}

/* getchar: simple buffered version */
int getchar2(void){
  static char buf[BUFSIZ];
  static char *bufp = buf;
  static int n = 0;

  if(n == 0){ /* buffer is empty */
    n = read(0, buf, sizeof buf);
    bufp = buf;
  }
  return (--n >= 0) ? (unsigned char)*bufp++ : EOF;
}
