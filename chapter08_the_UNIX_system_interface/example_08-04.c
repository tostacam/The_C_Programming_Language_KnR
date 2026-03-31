// 8.4 Random Access-Lseek

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int get(int, long, char *, int);

int main(){
  int fd;
  char buf[6]; // 5 chars + '\0'

  fd = open("test.txt", O_RDONLY);
  if(fd < 0){
    printf("can't open file\n");
    return 1;
  }
  if(get(fd, 0, buf, 5) > 0){ // read first 5 bytes
    buf[5] = '\0';
    printf("%s\n", buf);
  }

  close(fd);
  return 0;
}

/* get: read n bytes from position pos */
int get(int fd, long pos, char *buf, int n){
  if(lseek(fd, pos, 0) >= 0)  /* get to pos */
    return read(fd, buf, n);
  else 
    return -1;
}
