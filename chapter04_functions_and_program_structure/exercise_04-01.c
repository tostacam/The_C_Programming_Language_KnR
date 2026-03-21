// Exercise 4.1
// write the function strrindex(s,t), which returns the position
// of the rightmost occurrence of t in s, or -1 if there is none.

#include <stdio.h>
#include <string.h>

int strrindex(char source[], char searchfor[]);

/* find all lines matching pattern */
int main(){
  char str1[] = "hence, position of the rightmost ocurrence?";
  char str2[] = "write the function strrindex(s,t)";
  char pattern[] = "ence";  /* patter to search for */

  int n = strrindex(str1, pattern);
  if(n > 0)
    printf("found at index: %d\n", n);
  else
    printf("not found\n");
  
  n = strrindex(str2, pattern);
  if(n > 0)
    printf("found at index: %d\n", n);
  else
    printf("not found\n");
}

/* strrindex: return the rightmost occurrence of t in s */
int strrindex(char s[], char t[]){
  int i, j, k;

  for(i = strlen(s) - 1; i > 0; --i){
    for(j = i, k = strlen(t) - 1; j > 0 && s[j] == t[k]; --j, --k)
    if(k == 0)
      return i - (strlen(t) - 1);
  }
  return -1;
}
