// Exercise 4.12
// adapt the ideas of printd to write a recursive version of itoa;
// that is, convert an integer into a string by calling a recursive
// routine

#include <stdio.h>
#define MAXLINE 1000

void itoa(int n, char s[]);

int main(){
  int n;
  char s[MAXLINE];

  n = -12345;
  itoa(n, s);
  printf("[%d] -> itoa -> [\"%s\"]\n", n, s);

  n = 65789390;
  itoa(n, s);
  printf("[%d] -> itoa -> [\"%s\"]\n", n, s);
}

/* itoa: convert integert into a string */
void itoa(int n, char s[]){
  static int i;

  if(n / 10)
    itoa(n / 10, s); 
  else{
    i = 0;
    if(n < 0)
      s[i++] = '-';
  }
  
  s[i++] = (n > 0) ? (n % 10) + '0': (-n % 10) + '0';
  s[i] = '\0';
}
