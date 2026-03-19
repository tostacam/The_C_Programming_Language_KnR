// Exercise 2.5
// write the function any(s1, s2), which returns the first location in
// the string s1 where any character from the string s2 occurs, or -1 if
// s1 contains no characters from s2. (the standard library function
// strpbrk does the same job but returns a pointer to the location)/

#include <stdio.h>

int any(char s1[], char s2[]);

int main(){
  char s1[] = "hello, world";
  char s2[] = "ol";

  printf("first element of [%s] found in [%s] at : %d\n", s1, s2, any(s1, s2)); 

  char s3[] = "abc";
  char s4[] = "xyz";

  printf("first element of [%s] found in [%s] at : %d\n", s3, s4, any(s3, s4)); 
}

int any(char s1[], char s2[]){
  int i, j;

  for(i = 0; s1[i] != '\0'; ++i)
    for(j = 0; s2[j] != '\0'; ++j)
      if(s1[i] == s2[j]){
        return i;
      
  return -1;
}
