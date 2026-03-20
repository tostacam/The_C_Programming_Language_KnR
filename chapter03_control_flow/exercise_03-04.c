// Exercise 3.4
// in a two's complement number representation, our version of
// itoa does not handle the largest negative number, that is,
// the value of n equal to -(2^(wordsize-1)). explain why not.
// modify it to print that value correclty, regardless of the
// machine on which it runs. (see example 3.6)

#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAXLINE 1000

void reverse(char s[]);
void itoa(int n, char s[]);

int main(){
  int n = INT_MIN;  /* -(2^(wordsize-1)) */
  char s[MAXLINE];

  itoa(n, s);
  printf("[int: %d] -> [string: %s]", n, s);
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

/* itoa: convert n to characters in s */
void itoa(int n, char s[]){
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
  
  s[i] = '\0';

  reverse(s);
}
