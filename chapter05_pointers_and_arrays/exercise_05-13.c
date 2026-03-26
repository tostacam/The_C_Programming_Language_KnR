// Exercise 5.13
// Write the program tail, which prints the last n lines of its input.
// By default, n is 10, let us say, but it can be changed by an optional
// argument, so that
//
//   tail -n
//
// prints the last n lines. The program should behave rationally no matter
// how unreasonable the input or the value of n. Write the program so it
// makes the best use of available storage; lines should be stored as in
// the sorting program of Section 5.6, not in a two-dimensional array of
// fixed size.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define DEFAULT 10
#define MAXLINE 1000
#define ALLOCSIZE 1000  /* size of available space */

int getline_imp(char s[], int lim);
char *alloc(int n);

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

int main(int argc, char *argv[]){
  int c, j, len;
  char line[MAXLINE];
  char num[MAXLINE];
  int n = DEFAULT;

  while(--argc > 0 && ((c = (*++argv)[0]) == '-' || c == '+')){
    j = 0;
    while(isdigit(c = *++argv[0]))
      num[j++] = c;
    num[j] = '\0';

    n = atoi(num);
  }

  char *p;
  while((len = getline_imp(line, MAXLINE)) > 0){
    p = alloc(len);
    for(int i = 0; i < len; ++i)
      *p++ = line[i];
  }

  char *start = allocbuf;
  int count = 0;
  
  for(char *ptr = p - 1; ptr >= allocbuf; --ptr){
    if(*ptr == '\n'){
      if(count++ == n){
        start = ptr + 1;
        break;
      }
    }
  }

  for(char *ptr = start; ptr < p; ++ptr)
    putchar(*ptr);
}

int getline_imp(char s[], int lim){
  int c, i;

  for(i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if(c == '\n'){
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  
  return i;
}

/* return pointer to n characters */
char *alloc(int n){
  if(allocbuf + ALLOCSIZE - allocp >= n){  /* it fits */
    allocp += n;
    return allocp - n;    /* old p */
  }
  else                    /* not enough room */
    return 0;
}
