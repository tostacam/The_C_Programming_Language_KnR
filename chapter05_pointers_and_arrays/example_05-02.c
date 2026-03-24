// 5.2 Pointers and Function Arguments

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
    if(n != 0)
      printf("read: %d\n", val);
  }

  return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn){
  int c, sign;

  while(isspace(c = getch()));   /* skip white space */

  if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if(c == '+' || c == '-')
    c = getch();
  
  for(*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  *pn *= sign;
  if(c != EOF)
    ungetch(c);

  return c;
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
