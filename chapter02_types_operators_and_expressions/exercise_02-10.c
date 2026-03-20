// Exercise 2.10
// rewrite the function lower, which converts upper case letters
// to lower case, with a conditional expression instead of if-else

#include <stdio.h>

int lower(int c);

int main(){
  char upp = 'B', low;

  low = lower(upp);

  printf("char \'%c\' to lower case: %c\n", upp, low);
}

/* lower: convert c to lower case; ASCII only */
int lower(int c){
  return ('A' <= c && c <= 'Z') ? c + 'a' - 'A' : c;
}
