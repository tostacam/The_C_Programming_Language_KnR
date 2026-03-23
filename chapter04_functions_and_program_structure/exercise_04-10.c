// Exercise 4.10
// an alternate organization uses getline to read an entire input
// line; this makes getch and ungetch unnecessary. revise the
// calculator to use this approach.

// (note: most code from 4.3 External Variables + prev ex 4.9)

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXLINE 1000
#define MAXOP   100 /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL  100 /* maximum depth of val stack */
#define ERROR   1
#define MATHLIB 'm'
#define VAR     '1'

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
int error_flag = 0;
double variable[26] = {0.0};
char latestVar = -1;
double lastPrintVal;

int getop(char []);
void push(double);
double pop(void);
int getline_imp(char s[], int lim);

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
  static char line[MAXLINE];
  static int pos = 0;
  static int len = 0;

  int i = 0;

  // refill buffer if needed
  if (pos >= len) {
    if (fgets(line, MAXLINE, stdin) == NULL)
        return EOF;
    pos = 0;
    len = strlen(line);
  }

  // skip whitespace
  while (line[pos] == ' ' || line[pos] == '\t')
    pos++;

  // end of line
  if (line[pos] == '\n') {
    pos++;
    return '\n';
  }

  // number (including negative)
  if (isdigit(line[pos]) || line[pos] == '.' ||
    (line[pos] == '-' && isdigit(line[pos+1]))) {

    if (line[pos] == '-')
        s[i++] = line[pos++];

    while (isdigit(line[pos]))
        s[i++] = line[pos++];

    if (line[pos] == '.')
        s[i++] = line[pos++];

    while (isdigit(line[pos]))
        s[i++] = line[pos++];

    s[i] = '\0';
    return NUMBER;
  }

  // variable (single uppercase letter)
  if ('A' <= line[pos] && line[pos] <= 'Z') {
    push(line[pos]);
    s[0] = line[pos++];
    s[1] = '\0';
    return VAR;
  }

  // word (math functions)
  if (isalpha(line[pos])) {
    while (isalpha(line[pos]))
        s[i++] = line[pos++];

    s[i] = '\0';
    return MATHLIB;
  }

  // operator
  return line[pos++];
} 

/* getline: get line into s, return length */
int getline_imp(char s[], int lim){
  int c, i;

  i = 0;
  while(--lim > 0 && (c = getchar()) != EOF && c!= '\n')
    s[i++] = c;

  if(c == '\n')
    s[i++] = c;

  s[i] = '\0';
  return i;
}
