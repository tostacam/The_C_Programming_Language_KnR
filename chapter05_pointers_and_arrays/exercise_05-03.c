// Exercise 5.3
// write a pointer version of the function strcat that we showed
// in chapter 2: strchat(s,t) copies the string t to the end of s.

#include <stdio.h>

void strcat_imp(char *s, char *t);

int main(){
  char s[100] = "hello ";
  char t[] = "world";

  strcat_imp(s, t);
  printf("%s\n", s);
}

void strcat_imp(char *s, char *t){
  if(*s)
    while(*(++s));
  while((*s++ = *t++));
}
