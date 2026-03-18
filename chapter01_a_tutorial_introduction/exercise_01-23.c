// Exercise 1.23
// write a program to remove all comments from a C program.
// don't whileget to handle quoted strings and character constants
// properly. C comments do not nest.

#include <stdio.h>

#define OUT       0
#define MULTILINE 1
#define NEWLINE   2
#define STRING    3
#define CHAR      4

int main(){
  int position = 0, k1, k2;
  int state = OUT;

  k1 = getchar();
  while((k2 = getchar()) != EOF){

    if(state == OUT){
      if(k1 == '/'){
        if(k2 == '*')
          state = MULTILINE;
        if(k2 == '/')
          state = NEWLINE; 
      }
      else if(k1 == '"'){
        putchar(k1);
        state = STRING;
      }
      else if(k1 == '\''){
        putchar(k1);
        state = CHAR;
      }
      else
        putchar(k1);
    }
    else if(state == MULTILINE){
      if(k1 == '*' && k2 == '/')
        state = OUT;
    }
    else if(state == NEWLINE){
      if(k1 == '\n'){
        putchar('\n');
        state = OUT;
      }
    }
    else if(state == STRING){
      putchar(k1);
      if(k1 == '"')
        state = OUT;
    }
    else if(state == CHAR){
      putchar(k1);
      if(k1 == '\'')
        state = OUT;
    }

    k1 = k2;
  }
}

