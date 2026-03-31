// Exercise 8.4
// The standard library function
//
//   int fseek(FILE *fp, long offset, int origin)
//
// is identical to lseek except that fp is a file pointer instead of a file
// descriptor and the return value is an int status not a position. Write fseek.
// Make sure that your fseek coordinate properly with the buffering done for the
// other functions of the library.

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/* minimal FILE structure */
typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

/* flags */
#define _READ  01
#define _WRITE 02
#define _UNBUF 04
#define _EOF   010
#define _ERR   020

#define BUFSIZE 1024

FILE *fopen_imp(char *name, char *mode);
int fread_imp(char *buf, int size, int n, FILE *fp);
int fflush(FILE *fp);
int fseek(FILE *fp, long offset, int origin);
void print(char *s);
void print_buf(char *buf, int n);

int main() {
  FILE *fp = fopen_imp("test.txt", "r");
  char buf[6];

  if(!fp){
    print("failed to open file\n");
    return 1;
  }

  fread_imp(buf, 1, 5, fp);
  buf[5] = '\0';
  print_buf(buf, 5);

  fseek(fp, 0, SEEK_SET);

  fread_imp(buf, 1, 5, fp);
  buf[5] = '\0';
  print_buf(buf, 5);

  return 0;
}

/* minimal fopen_imp (read only) */
FILE *fopen_imp(char *name, char *mode) {
  int fd;
  FILE *fp;

  if(*mode != 'r')
    return NULL;

  fd = open(name, O_RDONLY, 0);
  if(fd == -1)
    return NULL;

  fp = (FILE *) malloc(sizeof(FILE));
  if(fp == NULL)
    return NULL;

  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->ptr = NULL;
  fp->flag = _READ;

  return fp;
}

/* minimal fread_imp */
int fread_imp(char *buf, int size, int n, FILE *fp){
  int total = size * n;
  return read(fp->fd, buf, total);
}

/* minimal fflush (only for write, stub here) */
int fflush(FILE *fp){
  return 0;
}

/* fseek implementation */
int fseek(FILE *fp, long offset, int origin){
  if(!(fp->flag & (_READ | _WRITE)))
    return -1;

  if(fp->flag & _WRITE)
    if(fflush(fp) == -1)
      return -1;

  if(fp->flag & _READ)
    if(origin == SEEK_CUR)
      offset -= fp->cnt;

  if(lseek(fp->fd, offset, origin) < 0)
    return -1;

  fp->cnt = 0;
  fp->ptr = fp->base;

  return 0;
}

/* simple print using write */
void print(char *s){
  while(*s)
    write(1, s++, 1);
}

void print_buf(char *buf, int n){
  write(1, buf, n);
  write(1, "\n", 1);
}
