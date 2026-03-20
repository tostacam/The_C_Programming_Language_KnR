// 2.11 Conditional Expressions

#include <stdio.h>

int main(){
  int a = 0, b = 10, z;

  z = (a > b) ? a : b; /* z = max(a, b) */

  printf("%d", z);
}
