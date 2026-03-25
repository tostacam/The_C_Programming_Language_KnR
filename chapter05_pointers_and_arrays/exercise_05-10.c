// Exercise 5.10
// Write the program expr, which evaluates a reverse Polish
// expression from the command line, where each operator or 
// operand is a separate argument. For example,
//
//   expr 2 3 4 + *
//
// evalutes 2x(3+4)
//
// (note: most of the code from 4.3)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXOP   100
#define NUMBER  '0'
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
int buf [BUFSIZE]; /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char []);

int main(int argc, char *argv[]){
  char s[MAXOP];
  double op2;

  while(--argc > 0){
    ungetch(' ');
    ungets(*++argv);
    switch(getop(s)){
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if(op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    default:
      printf("error: unknown command %s\n", s);
      argc = 1;
      break;
    }
  }

  printf("\t%.8g\n", pop());
  return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[]){
  int i, c;
  
  while((s[0] = c = getch()) == ' ' || c == '\t');
  s[1] = '\0';

  if(!isdigit(c) && c != '.')
    return c;     /* not a number */

  i = 0;
  if(isdigit(c))  /* collect integer part */
    while(isdigit(s[++i] = c = getch()));

  if(c == '.')    /* collect fraction part */
    while(isdigit(s[++i] = c = getch()));

  s[i] = '\0';
  if(c != EOF)
    ungetch(c);

  return NUMBER;
}

/* push: push f onto value stack */
void push (double f){
  if(sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g", f);
}

/* pop: poop and return top value from the stack */
double pop(void){
  if(sp > 0)
    return val[--sp];
  else
    printf("error: stack empty");

  return 0.0;
}

/* get a (possibly pushed back) character */
int getch(void){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void ungetch(int c){
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters");
  else
    buf[bufp++] = c;
}

/* ungets: push back entire string onto input */
void ungets(char s[]){
  int len = strlen(s);
  while(len > 0)
    ungetch(s[--len]);
}
