// Exercise 3.5
// write a function itob(n,s,b) that converts the integer n into
// a base b character representation in the string s. in particular,
// itob(n,s,16) formats n as a hexadecimal integer in s.

#include <stdio.h>
#include <string.h>
#include <limits.h>
#define MAXLINE 1000

void reverse(char s[]);
void itob(int n, char s[], int b);

int main(){
  int n = INT_MIN;  /* -(2^(wordsize-1)) */
  int b = 2;
  char s[MAXLINE];

  itob(n, s, b); 
  printf("[int: %d] -> [base %d: %s]\n", n, b, s);

  n = 255;
  b = 16;
  
  itob(n, s, b); 
  printf("[int: %d] -> [base %d: %s]\n", n, b, s);
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

/* itob: convert n to base b characters in s */
void itob(int n, char s[], int b){
  int i, sign;
  unsigned num;

  if((sign = n) < 0)
    num = 0 - (unsigned)n;  /* looping around unsigned number */
  else
    num = n;

  int baseChar[37];
  for(int j = 0; j < b; ++j){
    if(j < 10)
      baseChar[j] = j + '0';
    else
      baseChar[j] = j - 10 + 'a';
  }

  i = 0;
  do{
    s[i++] = baseChar[num % b];
  } while((num /= b) > 0);

  if(sign < 0)
    s[i++] = '-';

  s[i] = '\0';

  reverse(s);
}
