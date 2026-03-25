// Exercise 5.5
// Write versions of the library functions strncpy_imp, strncat_imp, and
// strncmp, which operate on at most the first n characters of their
// argument strings. For example, strncpy_imp(s,t,n) copies at most n characters
// of t to s. Full descriptions are in appendix B.

#include <stdio.h>

void strncpy_imp(char *s, char *t, int n);
void strncat_imp(char *s, char *t, int n);
int strncmp_imp(char *s, char *t, int n);

int main(){
  char s1[100];
  
  strncpy_imp(s1, "hello", 3);
  s1[3] = '\0'; 
  printf("%s\n", s1);

  strncpy_imp(s1, "hi", 5);
  printf("%s\n", s1);

  strncpy_imp(s1, "hello", 5);
  strncat_imp(s1, " world", 3);
  printf("%s\n", s1);

  strncpy_imp(s1, "abc", 3);
  strncat_imp(s1, "def", 10);
  printf("%s\n", s1);

  int result;

  result = strncmp_imp("hello", "helium", 3);
  printf("%d\n", result);

  return 0;
}

/* strncpy_imp: copy first n characters from t to s */
void strncpy_imp(char *s, char *t, int n){
  while((*s++ = *t++) && n-- > 0);
}

/* strncat_imp: concatenate first n characters from t to s */
void strncat_imp(char *s, char *t, int n){
  if(*s)
    while(*(++s));
  while(n-- > 0 && (*s++ = *t++));
}

/* strncmp: return <0 if s<t, 0 if s==t, >0 if s>t for first n chars*/
int strncmp_imp(char *s, char *t, int n){
  while((*s == *t) && n-- > 0){
    if(*s == '\0' || n == 0)
      return 0;

    ++s;
    ++t;
  }
  return *s - *t;
}

