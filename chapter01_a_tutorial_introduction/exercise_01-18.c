// Exercise 1.18
// write a program to remove trailing blanks and tabs from 
// each line of input, and to delete entirely blank lines

#include <stdio.h>
#define MAXLINE 1000

int getline_imp(char line[], int maxline);

int main(){
  int len, i, j;
  char line[MAXLINE];

  while((len = getline_imp(line, MAXLINE)) > 0){
    i = len - 1;
    while(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
      --i;
    for(j = 0; j <= i; ++j)
      printf("%c", line[j]);
    printf("\n");
  }
  
  return 0;
}

/* getline: read a line into s, return length */
int getline_imp(char s[], int lim){
  int c, i;

  for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if(c == '\n'){
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}
