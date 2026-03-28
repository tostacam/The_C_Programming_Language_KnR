// Exercise 7.2
// Write a program that will print arbitrary input in a sensible way.
// As a minimum, it should print non-graphic characters in octal or 
// hexadecimal according to local custom, and break long text lines.

#include <stdio.h>
#include <ctype.h>

int main(){
  int c, lineMax = 0;

  while((c = getchar()) != EOF){
    if(lineMax > 10){
      putchar('\n');
      lineMax = 0;
    }
    if(isalpha(c) || isdigit(c)){
      ++lineMax;
      putchar(c);
    }
    else{
      lineMax = lineMax + 4;
      printf("\\x%.2x", (int)c);
    }
  }
}
