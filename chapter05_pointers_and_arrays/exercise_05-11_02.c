// Exercise 5.11
// Modify the programs entab and detab (written as exercises in
// Chapter 1.21) to accept a list of tab stops as arguments. Use
// the default tab settings if there are no arguments.

#include <stdio.h>

#define TABSIZE 4

int main(int argc, char *argv[]){
  int c, col = 0, spaces, i = 1, j = 0;

  // ./a.out $'hello\tworld'

  while(--argc > 0){
    while((c = argv[i][j++]) != '\0'){
      if(c == '\t'){
        spaces = TABSIZE - (col % TABSIZE);
        for(int k = 0; k < spaces; ++k){
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
    ++i;
  }
}
