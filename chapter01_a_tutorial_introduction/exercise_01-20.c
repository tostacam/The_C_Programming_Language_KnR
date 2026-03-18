// Exercise 1.20
// write a program detab that replaces tabs in the input with the proper 
// number of blanks to space to the next tab stop. Assume a fixed set of
// tab stops, say every n columns. should n be a variable of a symbolic
// parameter?

#include <stdio.h>

#define TABSIZE 4

int main(){
  int c, col = 0, spaces, i;

  while((c = getchar()) != EOF){
    if(c == '\t'){
      spaces = TABSIZE - (col % TABSIZE);
      for(i = 0; i < spaces; ++i){
        putchar(' ');
        ++col;
      }
    }
    else if(c == '\n'){
      putchar(c);
      col = 0;
    }
    else{
      putchar(c);
      ++col;
    }   
  }
}
