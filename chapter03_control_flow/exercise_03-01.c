// Exercise 3.1
// our binary search makes two tests inside the loop, when one
// would suffice (at the price of more tests outside). write a
// version with only one test inside the loop and measure the 
// difference in run-time

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
  while(low < high){
    mid = (low + high) / 2;
    if(x <= v[mid])
      high = mid;
    else 
      low = mid + 1;
  }

  if(v[low] == x)
    return low;
  return -1;
}
