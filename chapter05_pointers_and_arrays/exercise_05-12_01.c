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
#define IN  1
#define OUT 0

int main(int argc, char *argv[]){
  int c, col = 0, blanks = 0, i = 1, j = 0, x;
  int quo, rem;  

  // ./a.out "hello        world"
  
  char num [1000];
  int tstart = 0;
  int tsize = TABSIZE;
 
  if(argc == 1){
    printf("no commands present\n");
    return 0;
  }

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
      if(c == ' '){
        ++blanks;
      }
      else{
        if(blanks == 0){
          ++col;
        }
        else{
          while (blanks > 0) {
            int next_tab;

            if (col < tstart)
              next_tab = tstart;
            else
              next_tab = tstart + ((col - tstart) / tsize + 1) * tsize;

            int spaces_to_tab = next_tab - col;

            if (blanks >= spaces_to_tab) {
              putchar('\t');
              col = next_tab;
              blanks -= spaces_to_tab;
            } else {
              putchar(' ');
              ++col;
              --blanks;
            }
          }          

          for(int k = 0; k < quo; ++k)
            putchar('\t');

          for(int k = 0; k < rem; ++k)
            putchar(' ');

          blanks = 0;
        }

        putchar(c);
      }
    }
  }

  return 0; 
}
