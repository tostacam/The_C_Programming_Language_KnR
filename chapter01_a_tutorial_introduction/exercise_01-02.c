// Exercise 1.2
// experiment to find out what happens when printf's argument
// string contains \c, where c is some character not listed above

#include <stdio.h>

int main(){

  // adding \z
  printf("hello,\z world\n");

  // compiler warning: unknown escape sequence '\z'
}
