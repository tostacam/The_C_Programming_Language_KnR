// Exercise 8.3
// Design and write _flushbuf, fflush, and fclose.

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
int _flushbuf(int c, FILE *fp);
int fflush(FILE *fp);
int fclose(FILE *fp);

int main(){
  FILE *fp;

  /* 1. open file for writing */
  fp = fopen_imp("test.txt", "w");
  if(fp == NULL){
    write(1, "open failed\n", 12);
    return 1;
  }

  /* 2. write enough chars to trigger _flushbuf */
  char *msg = "hello world (buffer test)\n";
  char *p = msg;

  while(*p)
    putc(*p++, fp);

  /* 3. force flush explicitly */
  fflush(fp);

  /* 4. write again after flush */
  char *msg2 = "after fflush\n";
  p = msg2;

  while(*p)
    putc(*p++, fp);

  /* 5. close (should flush remaining buffer) */
  fclose(fp);

  /* 6. read back using low-level syscalls to verify */
  int fd = open("test.txt", O_RDONLY);
  char buf[128];
  int n;

  write(1, "FILE CONTENT:\n", 14);

  while((n = read(fd, buf, sizeof(buf))) > 0)
    write(1, buf, n);

  close(fd);
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

/* _flushbuf: flush input buffer */
int _flushbuf(int c, FILE *fp){
  int n;

  if(!fp->flags._WRITE || fp->flags._ERR)
    return EOF;

  if(fp->base == NULL){
    int bufsize = fp->flags._UNBUF ? 1 : BUFSIZ;

    if((fp->base = (char *) malloc(bufsize)) == NULL)
      fp->flags._UNBUF = 1;
    else{
      fp->ptr = fp->base;
      fp->cnt = bufsize;
    }
  }

  if(fp->flags._UNBUF){
    if(c != EOF){
      char ch = c;
      if (write(fp->fd, &ch, 1) != 1){
        fp->flags._ERR = 1;
        return EOF;
      }
    }
    return c;
  }

  n = fp->ptr - fp->base;

  if(n > 0)
    if (write(fp->fd, fp->base, n) != n){
      fp->flags._ERR = 1;
      return EOF;
    }

  fp->ptr = fp->base;
  fp->cnt = BUFSIZ;

  if(c != EOF){
    *fp->ptr++ = c;
    fp->cnt--;
  }

  return c;
}

/* fflush: call _flushbuf without adding data */
int fflush(FILE *fp){
  if(fp == NULL){
    for(fp = _iob; fp < _iob + OPEN_MAX; fp++){
      if(fp->flags._WRITE && !fp->flags._ERR)
        fflush(fp);
    }
    return 0;
  }

  if(!fp->flags._WRITE)
    return EOF;

  return _flushbuf(EOF, fp);
}

/* fclose: close fd, free buffer and reset struct */
int fclose(FILE *fp){
  int rc = 0;

  if(fp->flags._WRITE)
    fflush(fp);

  rc = close(fp->fd);

  if(fp->base != NULL)
    free(fp->base);

  fp->cnt = 0;
  fp->ptr = NULL;
  fp->base = NULL;

  fp->flags._READ = 0;
  fp->flags._WRITE = 0;
  fp->flags._UNBUF = 0;
  fp->flags._EOF = 0;
  fp->flags._ERR = 0;

  return rc;
}
