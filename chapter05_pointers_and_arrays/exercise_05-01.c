// Exercise 5.1
// as written, getint treats a + or - not followed by a digit as
// a valid representation of zero. fix it to push such a character
// back on the input.

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getint(int *pn);
int getch(void);
void ungetch(int);

int main(){
  int n, val;

  while((n = getint(&val)) != EOF){
    if(n > 0)  
      printf("read: %d\n", val);
  }

  return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn){
  int c, temp, sign;

  while(isspace(c = getch()));   /* skip white space */

  if(c == EOF)
    return EOF;

  if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if(c == '+' || c == '-'){
    temp = c;

    c = getch();
    if(!isdigit(c)){
      if(c != EOF)
        ungetch(c);
      return 0;
    }
  }
  
  for(*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  *pn *= sign;
  if(c != EOF)
    ungetch(c);

  return 1;
}

int getch(void){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}
