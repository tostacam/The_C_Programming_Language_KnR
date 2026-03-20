// 3.8 Goto and Labels

#include <stdio.h>

int main(){

  int i, j;
  int n = 8, m = 5;
  int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int b[] = {-4, 10, 6, 15, -5};

  for(i = 0; i < n; ++i)
    for(j = 0; j < m; ++j)
      if(a[i] == b[j])
        goto found;
  
  printf("not found");
  return 0;
  
found:
  printf("found");
  return 0;
}
