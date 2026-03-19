// Exercise 2.6
// write a function setbits(x,p,n,y) taht returns x with the n
// bits that begin at position p set to the rightmost n bits of
// y, leaving the other bits unchanged.

#include <stdio.h>

void print_binary(unsigned x);
unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(){
  unsigned x = 0b10101010;
  unsigned y = 0b00001101;
  int p = 4;
  int n = 3;

  printf("x: 0b");
  print_binary(x);
  printf("y: 0b");
  print_binary(y);

  printf("r: 0b");
  print_binary(setbits(x, p, n, y));

}

void print_binary(unsigned x){
  for(int i = sizeof(x) * 8 - 1; i >= 0; --i)
    printf("%d", (x >> i) & 1);
  printf("\n");
}

unsigned setbits(unsigned x, int p, int n, unsigned y){
  return (~(~(~0 << n) << (p + 1 - n)) & x) /* cleared x n bits */
    | ((~(~0 << n) & y) << (p + 1 - n));    /* isolated y n bits */
}
