// Exercise 1.4
// write a program to print the corresponding
// Celsius to Farenheit table

#include <stdio.h>

int main(){
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;
  upper = 150;
  step = 10;

  printf("(C)  (F)\n");

  celsius = lower;
  while(celsius <= upper){
    fahr = ((9.0/5.0) * celsius) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
