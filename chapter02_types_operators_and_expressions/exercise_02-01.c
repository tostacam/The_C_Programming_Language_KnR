// Exercise 2.1
// write a program to determine the ranges of char, short,
// int, and long variables, both signed and unsigned, by printing
// appropiate values from standard headers and by direct computation.
// Harder if you compute them: determine the ranges of the various
// floating types.

#include <stdio.h>
#include <limits.h>

int main(){

  // limits.h values
  printf("\n==limits.h values==\n\n");

  // int
  printf("[int]\n");
  printf("min: %d, max: %d\n", INT_MIN, INT_MAX);
  printf("[unsigned int]\n");
  printf("min: %u, max: %u\n", 0, UINT_MAX);

  // char
  printf("[char]\n");
  printf("min: %d, max: %d\n", CHAR_MIN, CHAR_MAX);
  printf("[unsigned char]\n");
  printf("min: %u, max: %u\n", 0, UCHAR_MAX);
  
  // short
  printf("[short]\n");
  printf("min: %hd, max: %hd\n", SHRT_MIN, SHRT_MAX);
  printf("[unsigned short]\n");
  printf("min: %u, max: %u\n", 0, USHRT_MAX);
  
  // long 
  printf("[long]\n");
  printf("min: %ld, max: %ld\n", LONG_MIN, LONG_MAX);
  printf("[unsigned long]\n");
  printf("min: %lu, max: %lu\n", 0UL, ULONG_MAX);

  // computing values
  printf("\n==computed values==\n\n");

  // int
  int int_max = 1;
  while(int_max > 0){
    int_max = int_max * 2;
  }
  unsigned int uint_max = ~0;

  printf("[int]\n");
  printf("min: %d, max: %d\n", -int_max, int_max - 1);
  printf("[unsigned int]\n");
  printf("min: %u, max: %u\n", 0, uint_max);

  // char
  char char_max = 1;
  while(char_max > 0){
    char_max = char_max * 2;
  }
  unsigned char uchar_max = ~0;

  printf("[char]\n");
  printf("min: %d, max: %d\n", -char_max, char_max - 1);
  printf("[unsigned char]\n");
  printf("min: %u, max: %u\n", 0, uchar_max);

  // short
  short short_max = 1;
  while(short_max > 0){
    short_max = short_max * 2;
  }
  unsigned short ushort_max = ~0;

  printf("[short]\n");
  printf("min: %hd, max: %hd\n", -short_max, short_max - 1);
  printf("[unsigned short]\n");
  printf("min: %u, max: %u\n", 0, ushort_max);

  // long
  long long_max = 1;
  while(long_max > 0){
    long_max = long_max * 2;
  }
  unsigned long ulong_max = ~0;

  printf("[long]\n");
  printf("min: %ld, max: %ld\n", -long_max, long_max - 1);
  printf("[unsigned long\n");
  printf("min: %lu, max: %lu\n", 0UL, ulong_max);
}
