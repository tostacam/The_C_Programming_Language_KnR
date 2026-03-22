// Exercise 4.4
// add commands to print the top element of the stack without 
// popping, to duplicate it, and to swap the top two elements.
// add a command to clear the stack.

// (note: most code from 4.3 External Variables + prev ex 4.3)

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100
#define ERROR   1

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf [BUFSIZE]; /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */
int error_flag = 0;

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

/* reverse Polish calculator */
int main(){
  int type;
  double op1, op2;
  char s[MAXOP];

  while((type = getop(s)) != EOF){
    if(error_flag){
      printf(" (stopping program...) \n");
      break;
    }
    else{
      switch(type){
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
            printf("error: zero divisor");
            error_flag = ERROR;
          break;
        case '%':
          op2 = pop();
          if(op2 != 0.0)
            push((int)pop() % (int)op2);
          else
            printf("error: zero modulus");
            error_flag = ERROR;
          break;
        case '?': /* print top element of the stack without popping */
          if(sp > 0)
            printf("stack top: %.2g\n", val[sp - 1]);
          else{
            printf("error: can't query, stack empty");
            error_flag = ERROR;
          }
          break;
        case 'd': /* duplicate top element of the stack */
          if(sp > 0){
            op2 = pop();
            push(op2);
            push(op2);
          }
          else {
            printf("error: no element to duplicate");
            error_flag = ERROR;
          }
          break;
        case 's': /* swap top two elements */
          if(sp > 1){
            op2 = pop();
            op1 = pop();
            push(op2);
            push(op1);
          }
          else{
            printf("error: can't swap, not enough elements");
            error_flag = ERROR;
          }
          break;
        case 'c': /* clear the stack */
          sp = 0;
          break;
        case '\n':
          printf("result = %.2g\n", pop());
          break;
        default:
          printf("error: unknown command \'%s\'", s);
          break;
      }
    }
  }

  return 0;
}

/* push: push f onto value stack */
void push (double f){
  if(sp < MAXVAL)
    val[sp++] = f;
  else{
    printf("error: stack full, can't push %g", f);
    error_flag = ERROR;
  }
}

/* pop: pop and return top value from the stack */
double pop(void){
  if(sp > 0)
    return val[--sp];
  else{
    printf("error: stack empty");
    error_flag = ERROR;
    return 0.0;
  }
}

/* getop: get next operator or numeric operand */
int getop(char s[]){
  int i, c, cNext;
  
  while((s[0] = c = getch()) == ' ' || c == '\t');
  s[1] = '\0';

  i = 0;
  if(!isdigit(c) && c != '.'){
    if(c == '-'){
      cNext = getch();
      if(!isdigit(cNext)){
        ungetch(cNext);
        return c;
      }
      else{
        c = cNext;
        ungetch(cNext);
      }
    }
    else{
      return c;
    }
  }
  
  if(isdigit(c))  /* collect integer part */
    while(isdigit(s[++i] = c = getch()));

  if(c == '.')    /* collect fraction part */
    while(isdigit(s[++i] = c = getch()));

  s[i] = '\0';
  if(c != EOF)
    ungetch(c);

  return NUMBER;
}

/* get a (possibly pushed back) character */
int getch(void){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void ungetch(int c){
  if(bufp >= BUFSIZE){
    printf("ungetch: too many characters");
    error_flag = ERROR;
  }
  else
    buf[bufp++] = c;
}
