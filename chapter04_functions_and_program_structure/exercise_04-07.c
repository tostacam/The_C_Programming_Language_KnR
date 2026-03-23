// Exercise 4.7
// write a routine ungets(s) that will push back an entire string
// onto the input. should ungets know about buf and bufp, or should
// it just use ungetch?

// (note: most code from 4.3 External Variables + prev ex 4.6)

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define BUFSIZE 100
#define ERROR   1
#define MATHLIB 'm'
#define VAR     '1'

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf [BUFSIZE]; /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */
int error_flag = 0;
double variable[26] = {0.0};
char latestVar = -1;
double lastPrintVal;

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void ungets(char s[]);

/* reverse Polish calculator */
int main(){
  int type;
  double op1, op2;
  char s[MAXOP];

  /* ungets(s) test */
  ungets("5 6 + 2 *\n");

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
        case MATHLIB:
          if(strcmp(s, "sin") == 0)
            if(sp > 0)
              push(sin(pop()));
            else{
              printf("error: not enough elements for math op");
              error_flag = ERROR;
            }
          else if(strcmp(s, "exp") == 0)
            if(sp > 0)
              push(exp(pop()));
            else{
              printf("error: not enough elements for math op");
              error_flag = ERROR;
            }
          else if(strcmp(s, "pow") == 0)
            if(sp > 1){
              op2  = pop();
              push(pow(pop(), op2));
            }
            else{
              printf("error: not enough elements for math op");
              error_flag = ERROR;
            }
          else if(strcmp(s, "sqrt") == 0)
            if(sp > 0)
              push(sqrt(pop()));
            else{
              printf("error: not enough elements for math op");
              error_flag = ERROR;
            }
          else{
            printf("error: math function not added");
            error_flag = ERROR;
          }
          break;
        case VAR:
          latestVar = (char)pop() - 'A';
          push(variable[latestVar]);
          break;
        case '=':
          if(sp > 0){
            pop();
            if(sp > 0){
              variable[latestVar] = pop();
            }
            else{
              printf("error: no value to assign");
              error_flag = ERROR;
            }
          }
          else{
            printf("error: no variable present");
            error_flag = ERROR;
          }
          break;
        case 'v':
          push(lastPrintVal);
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
          else{
            printf("error: zero divisor");
            error_flag = ERROR;
          }
          break;
        case '%':
          op2 = pop();
          if(op2 != 0.0)
            push((int)pop() % (int)op2);
          else{
            printf("error: zero modulus");
            error_flag = ERROR;
          }
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
          if(sp > 0){
            lastPrintVal = pop();
            printf("result = %.2g\n", lastPrintVal);
            push(lastPrintVal);
          }
          else
            printf("stack empty, *no result*\n");
          break;
        default:
          printf("error: unknown command \'%s\'", s);
          error_flag = ERROR;
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
      if(c == '\n' || c == EOF)
        return c;
      
      if(c == 'v')
        return c;

      if('A' <= c && c <= 'Z'){
        push(c);
        return VAR;
      }

      cNext = getch();
      if(cNext == ' ' || cNext == '\n'){
        ungetch(cNext);
        return c;
      }
      else{
        ungetch(cNext);
        while((s[++i] = c = getch()) != ' ' && c != '\t' && c != '\n');
        
        s[i] = '\0';
        if(c != EOF)
          ungetch(c);
        
        return MATHLIB;
      }
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

/* ungets: push back entire string onto input */
void ungets(char s[]){
  int len = strlen(s);
  void ungetch(int);
  
  while(len > 0)
    ungetch(s[--len]);
}
