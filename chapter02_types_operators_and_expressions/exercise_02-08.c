// Exxercise 2.8
// write a function rightrot(x,n) that returns the value of the
// integer x rotated to the right by n bit positions.

#include <stdio.h>

void print_binary(unsigned x);
unsigned rightrot(unsigned x, int n);

int main(){
  unsigned x = 0b10110010;
  int n = 2;

  printf("x: 0b");
  print_binary(x);
  
  printf("r: 0b");
  print_binary(rightrot(x, n));
}

void print_binary(unsigned x){
  for(int i = sizeof(x) * 8 - 1; i >= 0; --i)
    printf("%d", (x >> i) & 1);
  printf("\n");
}

unsigned rightrot(unsigned x, int n){
  unsigned lowbit;
  
  for(int i = 0; i < n; ++i){
    lowbit = x & 1; 
    lowbit = lowbit << (sizeof(x) * 8 - 1);
    x = (x >> 1) | lowbit;
  }

  return x;
}
