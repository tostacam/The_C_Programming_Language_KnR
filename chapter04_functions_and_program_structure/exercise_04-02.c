// Exercise 4.6
// extend atof to handle scientif notation of the form
//    123.45e-6
// where a floating-point number may be followed by e 
// or E and an optionally signed exponent.

#include <stdio.h>
#include <ctype.h>

/* rudimentary calculator */
int main(){
  double atof(char s[]);

  printf("[\"123\"] -> double -> %g\n", atof("123"));
  printf("[\"-123\"] -> double -> %g\n", atof("-123"));
  printf("[\"123.45\"] -> double -> %g\n", atof("123.45"));
  printf("[\"0.5\"] -> double -> %g\n", atof("0.5"));
  printf("[\".5\"] -> double -> %g\n", atof(".5"));
  printf("[\"1e2\"] -> double -> %g\n", atof("1e2"));
  printf("[\"1e-2\"] -> double -> %g\n", atof("1e-2"));
  printf("[\"123.45e2\"] -> double -> %g\n", atof("123.45e2"));
  printf("[\"123.45e-2\"] -> double -> %g\n", atof("123.45e-2"));
  printf("[\"-1.2e2\"] -> double -> %g\n", atof("-1.2e2"));
  
  return 0;
}

/* atof: convert string s to double */
double atof(char s[]){
  double val, power, expo, e_val;
  int i, sign, expo_sign;

  for(i = 0; isspace(s[i]); ++i);

  sign = (s[i] == '-') ? -1 : 1;

  if(s[i] == '+' || s[i] == '-')
    ++i;

  for(val = 0.0; isdigit(s[i]); ++i)
    val = 10.0 * val + (s[i] - '0');

  if(s[i] == '.')
    ++i;

  for(power = 1.0; isdigit(s[i]); ++i){
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  if(s[i] == 'e' || s[i] == 'E'){
    ++i;

    expo_sign = 1;
    if(s[i] == '-'){
      expo_sign = 0;
      ++i;
    }

    for(expo = 0; isdigit(s[i]); ++i)
      expo = 10 * expo + (s[i] - '0'); 

    e_val = 1.0;
    for(int j = 0; j < expo; ++j)
      e_val *= (expo_sign) ? 10.0 : 0.1;

    return sign * val / power * e_val;
  }
  else
    return sign * val / power;
}
