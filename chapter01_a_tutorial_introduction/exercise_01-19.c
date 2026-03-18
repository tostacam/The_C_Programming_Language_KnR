// Exercise 1.19
// write a function reverse() that reverses the character string s,
// use it to write a program that reverse its input a line at a time.

#include <stdio.h>
#define MAXLINE 1000

int getline_imp(char line[], int maxline);
void reverse(char s[]);

int main(){
  int len, i, j;
  char line[MAXLINE];

  while((len = getline_imp(line, MAXLINE)) > 0){
    reverse(line);
    printf("reversed: %s\n", line);
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

/* reverse: reverses a string s */
void reverse(char s[]){
  char temp;
  int i = 0, j;

  for(j = 0; s[j] != '\0'; ++j);
  --j;

  while(i < j){
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    ++i;
    --j;
  }
}
