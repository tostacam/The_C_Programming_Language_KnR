// Exercise 5.12
// Extend entab and detab to accept the shorthand
// 
//   entab -m +n
//
// to mean tab stops every n columns, starting at column m.
// Choose convenient (for the user) default behavior.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TABSIZE 4

int main(int argc, char *argv[]){
  int c, col = 0, spaces, j, next_tab;

  // ./a.out $'hello\tworld'

  char num [1000];
  int tstart = 0;
  int tsize = TABSIZE;

  while(--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')){
    if(c == '-'){
      j = 0;
      while(isdigit(c = *++argv[0]))
        num[j++] = c;
      num[j] = '\0';

      tstart = atoi(num);
    }   
    else if(c == '+'){
      j = 0;
      while(isdigit(c = *++argv[0]))
        num[j++] = c;
      num[j] = '\0';

      tsize = atoi(num);
    }   
  }

  ++argc;
  --argv;
  while(--argc > 0 && ++argv){
    while((c = *argv[0]++)){
      if(c == '\t'){
        if (col < tstart)
          next_tab = tstart;
        else
          next_tab = tstart + ((col - tstart) / tsize + 1) * tsize;
        spaces = next_tab - col;
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
  }
}
