// 7.3 Variable-length Argument Lists

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main(){
  minprintf("hello world\n");
  minprintf("int: %d\n", 42);
  minprintf("float: %f\n", 3.14);
  minprintf("string: %s\n", "test");
  minprintf("mixed: %d %f %s\n", 10, 2.5, "ok");

  return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...){
  va_list ap;         /* points to each unnamed arg in turn */
  char *p, *sval;
  int ival;
  double dval;

  va_start(ap, fmt);  /* make ap point to 1st unnamed arg */
  for(p = fmt; *p; p++){
    if(*p != '%'){
      putchar(*p);
      continue;
    }
    switch(*++p){
    case 'd':
      ival = va_arg(ap, int);
      printf("%d", ival);
      break;
    case 'f':
      dval = va_arg(ap, double);
      printf("%f", dval);
      break;
    case 's':
      for(sval = va_arg(ap, char *); *sval; sval++)
        putchar(*sval);
      break;
    default:
      putchar(*p);
      break; 
    }
  }
  va_end(ap);         /* clean up when done */
}
