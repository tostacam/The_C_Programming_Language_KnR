// Exercise 3.6
// write a version of itoa that accepts three arguments instead of
// two. the third argument is a minimum field width; the converted
// number must be padded with blanks on the left if necessary to 
// make it wide enough.

#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAXLINE 1000

void reverse(char s[]);
void itoa(int n, char s[], int w);

int main(){
  int n = INT_MIN;  /* -(2^(wordsize-1)) */
  char s[MAXLINE];
  int w = 13;

  itoa(n, s, w);
  printf("[int: %d] -> [string: \"%s\"]", n, s);
}

/* reverse: reverse string s in place */
void reverse(char s[]){
  int c, i, j;

  for(i = 0, j = strlen(s) - 1; i < j; ++i, --j){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/* itoa: convert n to characters in s with minimun w width */
void itoa(int n, char s[], int w){
  int i, sign;
  unsigned num;

  if((sign = n) < 0) 
    num = 0 - (unsigned)n;  /* looping around unsigned number */
  else
    num = n;
  i = 0;
  
  do{                      
    s[i++] = num % 10 + '0'; 
  } while((num /= 10) > 0); 

  if(sign < 0)
    s[i++] = '-';

  for(;i < w;)
    s[i++] = ' ';
  
  s[i] = '\0';

  reverse(s);
}
