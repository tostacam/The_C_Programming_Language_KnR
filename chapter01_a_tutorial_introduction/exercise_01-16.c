// Exercise 1.16
// revise the main routine of the longest-line program so it will
// correctly print the length of arbitrarily long input lines, and
// as much as possible of the text

#include <stdio.h>
#define MAXLINE 15  /* decreased size for testing */
#define NOTSET  0
#define SET     1

int getline_imp(char line[], int maxline);
void copy(char to[], char from[]);

int main(){
  int len, stored;
  int lenTotal = 0;
  char line[MAXLINE];
  char lineCopy[MAXLINE];

  stored = NOTSET;
  while((len = getline_imp(line, MAXLINE)) > 0){
    if(line[len - 1] != '\n'){
      if(stored == NOTSET){
        copy(lineCopy, line);
        stored = SET;
      }
      lenTotal = lenTotal + len;
    }
    else {
      printf("length: %d\n%s", lenTotal, lineCopy);
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[]){
  int i;

  i = 0;
  while((to[i] = from[i]) != '\0')
    ++i;
}
