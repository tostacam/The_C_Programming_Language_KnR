// Exercise 7.8
// Write a program to print a set of files, starting each new one on a
// new page, with a title and a running page count for each file.

#include <stdio.h>

#define MAXLINE 100
#define NEWPAGE 10

int main(int argc, char *argv[]){
  FILE *fp;
  char line[MAXLINE];
  int pageCount, lineCount;

  while(--argc > 0){
    if((fp = fopen(*++argv, "r")) == NULL){
      printf("doc print: can't open %s\n", *argv);
    }
    pageCount = 0, lineCount = 0;
    while(fgets(line, MAXLINE, fp) != NULL){
      if((lineCount % NEWPAGE) == 0)
        printf("===== %s - Page %d =====\n", *argv, ++pageCount);
      printf("%s", line);
      ++lineCount; 
    }
  }

  return 0;
}
