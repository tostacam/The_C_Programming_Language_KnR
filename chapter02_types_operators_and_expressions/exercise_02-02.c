// Exercise 2.2
// write a loop equivalent to the for loop above (example 1.9) 
// without using && or ||

#include <stdio.h>
#define MAXLINE 1000

int getline_imp(char line[], int maxline);

int main(){
  int len;
  char line[MAXLINE];

  while((len = getline_imp(line, MAXLINE)) > 0);

  return 0;
}

/* getline: read a line into s, return length */
int getline_imp(char s[], int lim){
  int c, i;

  for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)

  i = 0;  
  while(1){
    if(i < lim-1){
      if((c = getchar() != EOF)){
        if(c != '\n'){
          s[i] = c;
          ++i;
        }
        else
          break;
      }
      else
        break;
    }
    else
      break;
  }
  if(c == '\n'){
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}
