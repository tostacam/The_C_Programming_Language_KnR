// Exercise 1.22
// write a program to "fold" long input lines into two or more shorter
// lines after the last non-blank character that occures before the n-th
// column of input. Make sure your program does something intelligent with
// very long lines, and if there are no blanks or tabs begore the sepcified
// column.

#include <stdio.h>

#define MAXCOL  10
#define MAXLINE 1000

int main(){
  int c, lineSize = 0;
  int lineStart = 0, lineEnd = 0, lineBreak = 0;
  int line[MAXLINE];

  while((c = getchar()) != EOF){
    line[lineSize] = c;
    ++lineSize;
  }

  while(lineStart < lineSize){
    lineEnd = lineStart;
    lineBreak = -1;

    while((lineEnd - lineStart) < MAXCOL && lineEnd < lineSize){
      if(line[lineEnd] == ' ')
        lineBreak = lineEnd;
      ++lineEnd;
    }
    
    if(lineBreak == -1)
      lineBreak = lineEnd;
    
    for(int i = lineStart; i < lineBreak; ++i)
      putchar(line[i]);
    putchar('\n');

    lineStart = lineBreak;

    if(line[lineStart] == ' ')
      ++lineStart;
  }
}
