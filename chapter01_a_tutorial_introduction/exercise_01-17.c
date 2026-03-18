// Exercise 1.17
// write a program to print all input lines that are
// longer than 80 characters

#include <stdio.h>
#define MINLINE 80
#define MAXLINE 1000

int getline_imp(char line[], int maxline);

int main(){
  int len;
  char line[MAXLINE];

  while((len = getline_imp(line, MAXLINE)) > 0){
    if(len > MINLINE){
      printf("line: %s\n", line);
    }
    else {
      printf("line ignored (less than 80 chars)\n");
    }
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
