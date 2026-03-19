// Exercise 2.4
// write an alternate version of squeeze(s1, s2) that deletes
// each character in s1 that matches any character in the
// string s2

#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main(){
  char s1[] = "hello, world";
  char s2[] = "ol";

  printf("[%s] -> deleting [%s] -> ", s1, s2);
  squeeze(s1, s2);
  printf("[%s]\n", s1);
}

void squeeze(char s1[], char s2[]){
  int i, j, k;

  k = 0;
  for(i = 0; s1[i] != '\0'; ++i){
    for(j = 0; s2[j] != '\0'; ++j){  
      if(s1[i] == s2[j])
        break;
    }
    if(s2[j] == '\0')
      s1[k++] = s1[i];
  }

  s1[k] = '\0';
} 
