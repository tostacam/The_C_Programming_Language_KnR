// Exercise 1.12
// write a program that prints ints input one
// word per line

#include <stdio.h>

#define IN  1
#define OUT 0

/* count lines, words, and characters in input */
int main(){
  int c, state;

  state = OUT;
  while((c = getchar()) != EOF){
    if(c == ' ' || c == '\n' || c == '\t'){
      if(state == IN){
        putchar('\n');
        state = OUT;
      }
    }
    else{
      putchar(c);
      state = IN;
    }
  }
}
