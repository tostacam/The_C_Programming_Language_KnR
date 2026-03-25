// Exercise 5.6
// Rewrite appropiate programs from earlier chapters and exercises
// with pointers instead of array indexing. Good possibilities include
// getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2,
// 3, and 4) reverse (Chapter 3), and strindex and getop (Chapter 4).

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int getline_imp(char *s, int lim);
int atoi(char *s);
void itoa(int n, char *s);
void reverse(char *s);
int strindex(char *source, char *searchfor);

int main(){
  char line[100];
  char s[100];

  /* getline + atoi */
  printf("Enter number: ");
  getline_imp(line, 100);
  printf("atoi: %d\n", atoi(line));

  /* itoa */
  itoa(1234, s);
  printf("itoa(1234): %s\n", s);

  itoa(-567, s);
  printf("itoa(-567): %s\n", s);

  /* reverse */
  strcpy(s, "hello");
  reverse(s);
  printf("reverse: %s\n", s);

  /* strindex */
  printf("strindex: %d\n", strindex("hello world", "world"));

  return 0;
}

/* getline: read a line into s, return length */
int getline_imp(char *s, int lim){
  int c, i;

  for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    *(s+i) = c;
  if(c == '\n'){
    *(s+i) = c;
    ++i;
  }
  *(s+i) = '\0';

  return i;
}

/* atoi: convert s to integer; version 2 */
int atoi(char *s){
  int i, n, sign;

  for(i = 0; isspace(*(s+i)); ++i); /* skip white space */
  sign = (*(s+i) == '-') ? -1 : 1;
  if(*(s+i) == '+' || *(s+i) == '-') /* skip sign */
    i++;

  for(n = 0; isdigit(*(s+i)); ++i)
    n = 10 * n + (*(s+i) - '0');

  return sign * n;
}

/* itoa: convert n to characters in s */
void itoa(int n, char *s){
  int i, sign;

  if((sign = n) < 0)  /* record sign */
    n = -n;           /* make n positive */
  i = 0;
  
  do{                       /* generate digits in reverse order */
    *(s+i++) = n % 10 + '0';  /* get next digit*/    
  } while((n /= 10) > 0);   /* delete it */

  if(sign < 0)
    *(s+i++) = '-';
  
  *(s+i++) = '\0';

  reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char *s){
  int c, i, j;

  for(i = 0, j = strlen(s) - 1; i < j; ++i, --j){
    c = *(s+i);
    *(s+i) = *(s+j);
    *(s+j) = c;
  }
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t){
  int i, j, k;

  for(i = 0; *(s+i) != '\0'; ++i){
    for(j = i, k =0; *(t+k) != '\0' && *(s+j) == *(t+k); ++j, ++k);
    if(k > 0 && *(t+k) == '\0')
      return i;
  }
  return -1;
}
