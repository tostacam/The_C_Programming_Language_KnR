// Exercise 4.14
// define a macro swap(t,x,y) that interchanges two arguments
// of type t. (block structure will help)

#include <stdio.h>
#define swap(t,x,y) { t tmp = (x); (x) = (y); (y) = tmp; }

int main(){
  int a = 3, b = 8;

  printf("a: %d, b: %d\n", a, b);
  swap(int, a, b);
  printf("a: %d, b: %d\n", a, b);
}
