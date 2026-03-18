// Exercise 1.15
// rewrite the temperature conversion program of section
// 1.2 to use a function for conversion

#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

float celsius(int fahr);

int main(){
  int fahr;

  for(fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
    printf("%3d %6.1f\n", fahr, celsius(fahr));
}

float celsius(int fahr){
  return (5.0/9.0)*(fahr-32.0);  
}
