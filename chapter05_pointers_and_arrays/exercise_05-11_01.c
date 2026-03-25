// Exercise 5.11
// Modify the programs entab and detab (written as exercises in
// Chapter 1.21) to accept a list of tab stops as arguments. Use
// the default tab settings if there are no arguments.

#include <stdio.h>

#define TABSIZE 4
#define IN  1
#define OUT 0

int main(int argc, char *argv[]){
  int c, col = 0, blanks = 0, i = 1, j = 0;
  int quo, rem;  

  // ./a.out "hello        world"

  while(--argc > 0){
    while((c = argv[i][j++]) != '\0'){
      if(c == ' '){
        ++blanks;
      }
      else{
        if(blanks == 0){
          ++col;
        }
        else{
          quo = blanks / TABSIZE;
          rem = blanks % TABSIZE;
          
          for(int k = 0; k < quo; ++k)
            putchar('\t');

          for(int k = 0; k < rem; ++k)
            putchar(' ');

          blanks = 0;
        }

        putchar(c);
      }
    }
    ++i;
  }  
}
