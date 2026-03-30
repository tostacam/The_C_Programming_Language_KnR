// Exercise 7.4
// Write a private version of scanf analogous to minprintf from
// the previous section.

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minscanf(char *fmt, ...);

int main(){
  int x;
  char s[100];
  double f;
  minscanf("%d %s %f", &x, s, &f);
  printf("%d %s %.1f\n", x, s, f);
}

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...){
  va_list ap; /* points to each unnamed arg in turn */
  int *ival;
  double *dval;
  char *p, *sval;

  va_start(ap, fmt);
  for(p = fmt; *p; p++){
    if(*p != '%'){
      getchar();
      continue;
    }
    switch(*++p){
    case 'd':
      ival = va_arg(ap, int*);
      scanf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double*);
      scanf("%lf", dval);
      break;
    case 's':
      sval = va_arg(ap, char*);
      scanf("%s", sval);
      break;
    default:
      getchar();
      break; 
    }
  }
  va_end(ap); 
}
