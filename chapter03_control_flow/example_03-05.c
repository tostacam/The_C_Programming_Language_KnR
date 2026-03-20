// 3.5 Loops-While and For

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int atoi(char s[]);
void shellsort(int v[], int n);
void reverse(char s[]);

int main(){
  char s[] = "-12345";
  int n;

  // atoi
  n = atoi(s);

  // shellsort
  int arr[] = {4, 1, 8, 3, 6, 9, 2, 7, 5};
  shellsort(arr, 9);

  // string reverse
  reverse(s);
}

/* atoi: convert s to integer; version 2 */
int atoi(char s[]){
  int i, n, sign;

  for(i = 0; isspace(s[i]); ++i); /* skip white space */
  sign = (s[i] == '-') ? -1 : 1;
  if(s[i] == '+' || s[i] == '-') /* skip sign */
    i++;
  
  for(n = 0; isdigit(s[i]); ++i)
    n = 10 * n + (s[i] - '0');

  return sign * n;
}

/* shellsort: sort v[0]...v[n-1] into increasing order */
void shellsort(int v[], int n){
  int gap, i, j, temp;

  for(gap = n/2; gap > 0; gap /= 2)
    for(i = gap; i < n; ++i)
      for(j = i-gap; j >= 0 && v[j] > v[j+gap]; j -= gap){
        temp = v[j];
        v[j] = v[j+gap];
        v[j+gap] = temp;
      }
}

/* reverse: reverse string s in place */
void reverse(char s[]){
  int c, i, j;

  for(i = 0, j = strlen(s) - 1; i < j; ++i, --j){
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
