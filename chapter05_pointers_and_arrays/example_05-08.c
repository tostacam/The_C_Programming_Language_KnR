// 5.8 Initialization of Pointer Arrays

#include <stdio.h>

/* month name: return name of n-th month */
char *month_name(int n){
  static char *name[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
  };

  return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(){
  int month = 12;
  char *pm;

  pm = month_name(month);

  while(*pm)
    putchar(*pm++);
  putchar('\n');
}
