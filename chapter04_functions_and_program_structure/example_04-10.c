// 4.10 Recursion

#include <stdio.h>

void printd(int n);
void qsort(int v[], int left, int right);
void swap(int v[], int i, int j);

int main(){
  int n = 1000;
  printd(n);

  int v[] = {4, 5, 2, 9, 8, 3, 1, 7, 6};
  qsort(v, 0, 8);
}

/* printd: print n in decimal */
void printd(int n){
  if(n < 0){
    putchar('-');
    n = -n;
  }
  if(n / 10)
    printd(n / 10);
  putchar(n % 10 + '0');
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right){
  int i, last;
  void swap(int v[], int i, int j);

  if(left >= right)                   /* do nothing if array contains */
    return;                           /* fewer than two elements */

  swap(v, left, (left + right)/2);    /* move partition elem */
  last = left;                        /* to v[0] */

  for(i = left + 1; i <= right; ++i)  /* partition*/
    if(v[i] < v[left])
      swap(v, ++last, i);

  swap(v, left, last);                /* restore partition elem */
  qsort(v, left, last - 1);
  qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j){
  int temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
