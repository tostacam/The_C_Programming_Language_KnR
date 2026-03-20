// Exercise 2.9
// in a two's complement number system, x &= (x-1) deletes the
// rightmost 1-bit in x. explain why. use this observation to 
// write a faster version of bitcount.

#include <stdio.h>

int bitcount(unsigned x);
int bitcount_fast(unsigned x);

int main(){
  unsigned x = 0b11010010;

  printf("number of \'1\' bits in x: %d\n", bitcount(x));
  printf("number of \'1\' bits in x (fast bitwise): %d\n", bitcount_fast(x));
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x){
  int b;

  for(b = 0; x != 0; x >>= 1)
    if(x & 01)
      ++b;

  return b;
}

/* bitcount: count 1 bits in x; faster version 
      x - 1 flips all bits after the right most 1
      ANDing removes that 1
      i.e.

      x = 11010000 
    x-1 = 11001111

      AND x & (x-1) all left bits unchanged, right most
      bit turned to 0

      much faster than traversing the whole unsigned number
      and checking each bit for a 1
   */
int bitcount_fast(unsigned x){
  int n = 0;

  while(x != 0){
    x &= (x - 1);
    ++n;
  }
    
  return n;
}
