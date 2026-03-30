// Exercise 7.9
// Functions like isupper can be implemented to save space or to 
// save time. Explore both possibilities.

#include <stdio.h>

int isupper_save_space(int c);
int isupper_save_time(int c);

int isupper_table[256] = {0};

int main(){
  // initializing_table
  for(int i = 'A'; i <= 'Z'; ++i)
    isupper_table[i] = 1;

  printf("%d\n", isupper_save_space('A'));
  printf("%d\n", isupper_save_time('A'));
  printf("%d\n", isupper_save_space('a'));
  printf("%d\n", isupper_save_time('a'));
}

int isupper_save_space(int c){
  return 'A' <= c && c <= 'Z';
}

int isupper_save_time(int c){
  return isupper_table[c];
}
