// Exercise 7.3
// Revise minprintf to handle more of the other facilities of
// printf.

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

void minprintf(char *fmt, ...);

int main(){
  minprintf("hello world\n");
  minprintf("int: %d\n", 42);
  minprintf("int width: %5d\n", 42);
  minprintf("float: %f\n", 3.14);
  minprintf("float precision: %.2f\n", 3.14159);
  minprintf("float both: %8.2f\n", 3.14159);
  minprintf("string: %s\n", "test");
  minprintf("string width: %10s\n", "hi");
  minprintf("mixed: %5d %.2f %-8s\n", 10, 2.5, "ok");
  return 0;
}

/* extended minprintf */
void minprintf(char *fmt, ...){
  va_list ap;
  char *p;
  char format[50];   // to build format like "%8.2f"
  int i;

  va_start(ap, fmt);
  for(p = fmt; *p; p++){
    if(*p != '%'){
      putchar(*p);
      continue;
    }

    i = 0;
    format[i++] = '%';
    p++;

    while(*p && !isalpha(*p)){
      format[i++] = *p;
      p++;
    }

    format[i++] = *p;
    format[i] = '\0';

    switch(*p){
      case 'd': {
        int ival = va_arg(ap, int);
        printf(format, ival);
        break;
      }
      case 'f': {
        double dval = va_arg(ap, double);
        printf(format, dval);
        break;
      }
      case 's': {
        char *sval = va_arg(ap, char *);
        printf(format, sval);
        break;
      }
      case 'x': {
        int ival = va_arg(ap, int);
        printf(format, ival);
        break;
      }
      case '%': {
        putchar('%');
        break;
      }
      default:
        putchar(*p);
        break;
    }
  }
  va_end(ap);
}
