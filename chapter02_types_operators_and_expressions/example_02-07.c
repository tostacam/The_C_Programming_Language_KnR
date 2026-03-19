// 2.7 Type Conversions

#include <stdio.h>

int atoi(char s[]);
int lower(int c);

int main(){
  char s[] = "1234";
  char upp = 'B', low;
  
  int n = atoi(s);
  low = lower(upp);

  printf("string \"%s\" to int: %d\n", s, n);
  printf("char \'%c\' to lower case: %c\n", upp, low);
}

/* atoi: convert s to integer */
int atoi(char s[]){
  int i, n;

  n = 0;
  for(i = 0; '0' <= s[i] && s[i] <= '9'; ++i)
    n = 10 * n + (s[i] - '0');
  return n;
}

/* lower: convert c to lower case; ASCII only*/
int lower(int c){
  if('A' <= c && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;
}
