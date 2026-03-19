// 2.9 Bitwise Operators

#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main(){
  unsigned x = 28;
  unsigned bits;

  bits = getbits(x, 4, 3);
  printf("%u", bits);
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n){
  return (x >> (p+1-n)) & ~(~0 << n);
}
