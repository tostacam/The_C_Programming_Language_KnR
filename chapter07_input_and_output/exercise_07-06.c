// Exercise 7.6
// Write a program to compare two files, printing the first line
// where they differ.

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int main(int argc, char *argv[]){
  FILE *fp1, *fp2;
  void filecmp(FILE *, FILE *);
  char *prog = argv[0];

  if(argc <= 2)
    printf("cmp: not enough files to compare\n");
  else{
    if((fp1 = fopen(*++argv, "r")) == NULL){
      fprintf(stderr, "%s: can't open %s\n", prog, *argv);
      exit(1);
    }
    if((fp2 = fopen(*++argv, "r")) == NULL){
      fprintf(stderr, "%s: can't open %s\n", prog, *argv);
      exit(1);
    }
    filecmp(fp1, fp2);
  }
}

void filecmp(FILE *f1, FILE *f2){
  char line1[MAXLINE], line2[MAXLINE];
  
  while(fgets(line1, MAXLINE, f1) != NULL && fgets(line2, MAXLINE, f2) != NULL)
    for(int i = 0; line1[i]; ++i)
      if(line1[i] != line2[i]){
        printf("files are not equal, mismatch at lines:\n");
        printf("file1: %sfile2: %s", line1, line2);
        return;
      }
  printf("files are equal!");
  return;
}
