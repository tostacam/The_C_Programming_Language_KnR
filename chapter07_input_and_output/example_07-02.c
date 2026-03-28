// 7.2 Formated Output-Printf

#include <stdio.h>

int main(){
  // width and precision parameters
  printf(":%s:\n", "hello, world");
  printf(":%10s:\n", "hello, world");
  printf(":%.10s:\n", "hello, world");
  printf(":%-10s:\n", "hello, world");
  printf(":%.15s:\n", "hello, world");
  printf(":%-15s:\n", "hello, world");
  printf(":%15.10s:\n", "hello, world");
  printf(":%-15.10s:\n", "hello, world");

  // sprintf(char *string, char *format, arg1, arg2, ...)
  //   only stores resulting string into a buffer
  char string[20];
  sprintf(string, "%s", "hello, world");
  printf("%s", string);
}
