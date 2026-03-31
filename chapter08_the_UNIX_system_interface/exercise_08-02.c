// Exercise 8.2
// Rewrite fopen and _fillbuf with fields instead of explicit bit
// operations. Compare code size and execution speed.

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;

    struct {
        unsigned int _READ  : 1;
        unsigned int _WRITE : 1;
        unsigned int _UNBUF : 1;
        unsigned int _EOF   : 1;
        unsigned int _ERR   : 1;
    } flags;

    int fd;
} FILE;

FILE _iob[OPEN_MAX] = {
    { 0, NULL, NULL, {1,0,0,0,0}, 0 },  /* stdin  */
    { 0, NULL, NULL, {0,1,0,0,0}, 1 },  /* stdout */
    { 0, NULL, NULL, {0,1,1,0,0}, 2 }   /* stderr (unbuffered) */
};

#define stdin   (&_iob[0])
#define stdout  (&_iob[1])
#define stderr  (&_iob[2])

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666  /* RW for owner, group, other */

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x,p) write((p)->fd, &(char){x}, 1)

FILE *fopen_imp(char *, char *);
int _fillbuf(FILE *);

int main(){
  char *msg = "hello world\n";

  while(*msg)
    putc(*msg++, stdout);
  putc('\n', stdout);

  return 0;
}

/* fopen_imp: open file, return file ptr */
FILE *fopen_imp(char *name, char *mode){
  int fd;
  FILE *fp;

  if(*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if(fp->flags._READ == 0 && fp->flags._WRITE == 0)
      break;                  /* found free slot */
  if(fp >= _iob + OPEN_MAX)   /* no free slots */
    return NULL;

  if(*mode == 'w')
    fd = creat(name, PERMS);
  else if(*mode == 'a'){
    if((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  }
  else
    fd = open(name, O_RDONLY, 0);

  if(fd == -1)    /* couldn't access name */
    return NULL;
  
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  
  fp->flags._READ = fp->flags._WRITE = fp->flags._UNBUF =
  fp->flags._EOF = fp->flags._ERR = 0; 

  if(*mode == 'r')
    fp->flags._READ = 1;
  else
    fp->flags._WRITE = 1;
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp){
  int bufsize;

  if(!fp->flags._READ || fp->flags._EOF || fp->flags._ERR)
    return EOF;

  bufsize = (fp->flags._UNBUF) ? 1 : BUFSIZ;
  if(fp->base == NULL)    /* no buffer yet */
    if((fp->base = (char *) malloc(bufsize)) == NULL)
      return EOF;         /* can't get buffer */
  
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if(--fp->cnt < 0){
    if(fp->cnt < 0)
      fp->flags._EOF = 1;
    else
      fp->flags._ERR = 1;
    fp->cnt = 0;
    return EOF;
  } 

  return (unsigned char) *fp->ptr++;
}
