// Exercise 1.3
// modify the temperature conversion program to print a 
// heading above the table

#include <stdio.h>

int main(){
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 300;
  step = 20;

  // added header
  printf("(F)  (C)\n");

  fahr = lower;
  while(fahr <= upper){
    celsius = (5.0/9.0)*(fahr-32.0);
    printf("%3.0f %6.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
