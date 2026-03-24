// 5.3 Pointers and Arrays

#include <stdio.h>

int main(){
  int i = 0;
  int a[] = {0,1,2,3,4,5,6,7,8,9};

  if(a[i] == *(a + i))
    printf("equal");
}
