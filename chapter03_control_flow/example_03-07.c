// 3.7 Break and Continue

#include <stdio.h>
#include <string.h>

int main(){
  /* remove trailing blanks, tabs, newlines */
  int n;
  char s[] = "hello world    ";

  printf("[\"%s\"] -> ", s);
  for(n = strlen(s)-1; n >= 0; --n)
    if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
      break;
  s[n+1] = '\0';
  printf("trim -> [\"%s\"]\n", s);

  /* skip negative numbers */
  int i, k = 7;
  int a[] = {1, -4, 5, 6, -7, 8, 9};

  printf("array: ");
  for(i = 0; i < k; ++i)
    printf("%d ", a[i]);

  printf("-> skip negatives -> ");
  for(i = 0; i < k; ++i){
    if(a[i] < 0)
      continue;
    printf("%d ", a[i]);
  }
}
