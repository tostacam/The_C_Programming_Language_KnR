// Exercise 4.13
// write a recursive version of the function reverse(s), which
// reverses the string s in place.

#include <stdio.h>
#include <string.h>

void reverse(char s[], int pos, int len);

int main(){
  char s[] =  "reversing string";

  printf("[\"%s\"] -> reverse -> ", s);
  reverse(s, 0, strlen(s));
  printf("[\"%s\"]", s);
}

/* reverse: reverse a string s */
void reverse(char s[], int pos, int len){
  int temp, posEnd;

  posEnd = len - (pos + 1);

  if(pos < posEnd){
    temp = s[pos];
    s[pos] = s[posEnd];
    s[posEnd] = temp;
    reverse(s, ++pos, len);
  }
}
