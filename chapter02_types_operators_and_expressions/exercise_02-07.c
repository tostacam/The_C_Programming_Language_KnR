// Exercise 2.7
// write a function invert(x,p,n) that returns x with the n bits
// that begin at position p inverted (i.e., 1 changed into 0 and
// vice versa), leaving the others unchanged.

#include <stdio.h>

void print_binary(unsigned x);
unsigned invert(unsigned x, int p, int n);

int main(){
  unsigned x = 0b10101010;
  int p = 4;
  int n = 3;

  printf("x: 0b");
  print_binary(x);  
  
  printf("r: 0b");
  print_binary(invert(x, p, n));  

  x = 0b00000000;
  p = 7;
  n = 8;

  printf("x: 0b");
  print_binary(x);  
  
  printf("r: 0b");
  print_binary(invert(x, p, n));  
}

void print_binary(unsigned x){ 
  for(int i = sizeof(x) * 8 - 1; i >= 0; --i)
    printf("%d", (x >> i) & 1); 
  printf("\n");
}

unsigned invert(unsigned x, int p, int n){
  return (~x >> (p + 1 -n)) & ~(~0 << n) << (p + 1 - n)   /* inverted x n bits */
    | ~(~(~0 << n) << (p + 1 - n)) & x;                   /* cleared x n bits */
}
