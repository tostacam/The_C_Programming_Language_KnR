// Exercise 1.21
// write a program entab that replaces strings of blanks by the
// minimum number of tabs and blanks to achieve the same spacing. use
// the same tab stops as for detab. when either a tab or a single blank
// would suffice to reach a tab stop, which should be given preference?

#include <stdio.h>

#define TABSIZE 4
#define IN  1
#define OUT 0

int main(){
  int c, col = 0, blanks = 0;
  int quo, rem;  

  while((c = getchar()) != EOF){
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
        
        for(int i = 0; i < quo; ++i)
          putchar('\t');

        for(int i = 0; i < rem; ++i)
          putchar(' ');

        blanks = 0;
      }

      putchar(c);
    }
  }  
}
