// Exercise 7.1
// Write a program that converts upper case to lower or lower case
// to upper, depending on the name it is invoked with, as found
// in argv[0].

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LOWER 1
#define UPPER 2

int main(int argc, char *argv[]){
  int convert = 0, c;

  if(strstr(argv[0], "lower"))
    convert = LOWER;
  else if(strstr(argv[0], "upper"))
    convert = UPPER;

  while((c = getchar()) != EOF)
    if(convert == LOWER && isalpha(c))
      putchar(tolower(c));
    else if(convert == UPPER && isalpha(c))
      putchar(toupper(c));
    else
      putchar(c);
}
