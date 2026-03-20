// 3.3 Else-If

#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(){
  int x = 4, n = 9;
  int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  
  printf("%d found at position: %d\n", x, binsearch(x, v, n));
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n){
  int low, high, mid;

  low = 0;
  high = n - 1;
  while(low <= high){
    mid = (low + high) / 2;
    if(x < v[mid])
      high = mid - 1;
    else if(v[mid] < x)
      low = mid + 1;
    else /* found match */
      return mid;
  }

  return -1;  /* no match */
}
