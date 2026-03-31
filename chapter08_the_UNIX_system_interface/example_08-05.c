// 8.5 Example-An Implementation of Fopen and Getc

#include <fcntl.h>
#include "syscalls.h"
#include <unistd.h>

FILE _iob[_OPEN_MAX] = {
  { 0, (char *) 0, (char *) 0, _READ, 0 },
  { 0, (char *) 0, (char *) 0, _WRITE, 1 },
  { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

#define PERMS 0666  /* RW for owner, group, other */

FILE *fopen_imp(char *name, char *mode);
int _fillbuf(FILE *fp);

int main(){
  FILE *fp = fopen_imp("test.txt", "r");

  if(fp == NULL){
    write(1, "fail\n", 5);
    return 1;
  }

  int c = _fillbuf(fp);

  if(c == EOF){
    write(1, "EOF or error\n", 13);
  } 
  else{
    write(1, "first char: ", 12);
    write(1, &c, 1);   // print the char
    write(1, "\n", 1);
  }

  return 0;
}

/* fopen_imp: open file, return file ptr */
FILE *fopen_imp(char *name, char *mode){
  int fd;
  FILE *fp;

  if(*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for(fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if((fp->flag & (_READ | _WRITE)) == 0)
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
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp){
  int bufsize;

  if((fp->flag&(_READ|_EOF|_ERR)) != _READ)
    return EOF;

  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if(fp->base == NULL)    /* no buffer yet */
    if((fp->base = (char *) malloc(bufsize)) == NULL)
      return EOF;         /* can't get buffer */
  
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if(--fp->cnt < 0){
    if(fp->cnt < 0)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  } 

  return (unsigned char) *fp->ptr++;
}
