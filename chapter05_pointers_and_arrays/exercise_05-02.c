// Exercise 5.2
// write getfloat, the floating-point analog of getint. what
// type does getfloat return as its function value?

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getfloat(float *pn);
int getch(void);
void ungetch(int);

int main(){
  int n;
  float val;

  while((n = getfloat(&val)) != EOF){
    if(n > 0)
      printf("read: %f\n", val);
  }

  return 0;
}

/* getint: get next integer from input into *pn */
int getfloat(float *pn){
  int c, sign;
  float power;

  while(isspace(c = getch()));   /* skip whitespace */

  if(c == EOF)
    return EOF;

  if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.'){
    ungetch(c);
    return 0;
  }

  sign = (c == '-') ? -1 : 1;

  if(c == '+' || c == '-'){
    int temp = c;
    c = getch();
    if(!isdigit(c) && c != '.'){
      if(c != EOF)
        ungetch(c);
      ungetch(temp);
      return 0;
    }
  }

  /* integer part */
  for(*pn = 0.0; isdigit(c); c = getch())
    *pn = 10.0 * (*pn) + (c - '0');

  /* fraction part */
  if(c == '.'){
    c = getch();
    for(power = 1.0; isdigit(c); c = getch()){
      *pn = 10.0 * (*pn) + (c - '0');
      power *= 10.0;
    }
    *pn /= power;
  }

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
