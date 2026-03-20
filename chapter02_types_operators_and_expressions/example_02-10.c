// 2.10 Assignment Operators and Expressions

#include <stdio.h>

int bitcount(unsigned x);

int main(){
  unsigned x = 0b11010010;

  printf("1 bits in x: %d\n", bitcount(x));
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x){
  int b;

  for(b = 0; x != 0; x >>= 1)
    if(x & 01)
      b++;

  return b;
}
