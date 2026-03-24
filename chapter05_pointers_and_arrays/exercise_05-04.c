// Exercise 5.4
// write the function strend(s,t), which returns 1 if the string 
// t occurs at the end of the string s, and zero otherwise.

#include <stdio.h>

int strend(char *s, char *t);

int main(){
  char s[100] = "hello world";
  char t[] = "rld";

  if(strend(s, t))
    printf("[\"%s\"] -> occurs at end of -> [\"%s\"]", t, s);
  else
    printf("[\"%s\"] -> doesn't occur at end of -> [\"%s\"]", t, s);
}

int strend(char *s, char *t){
  char *es = s;
  char *et = t;

  while(*es)
    es++;
  while(*et)
    et++;

  while(et > t){
    if(*(--es) != *(--et))
      return 0;
  }

  return 1;
}
