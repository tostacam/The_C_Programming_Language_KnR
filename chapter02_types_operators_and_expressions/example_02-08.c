// 2.8 Increment and Decrement Operators

#include <stdio.h>

void squeeze(char s[], int c);
void strcat_imp(char s[], char t[]);

int main(){
  char s[] = "hello, world";
  char c = 'o';

  printf("%s -> deleting %c -> ", s, c);
  squeeze(s, c);
  printf("%s\n", s);

  char str1[] = "concatenating ";
  char str2[] = "text strings";
  
  printf("str1[%s] + str2[%s] -> ", str1, str2);
  strcat_imp(str1, str2);
  printf("%s", str1);
}

/* squeeze: delete all c from s */
void squeeze(char s[], int c){
  int i, j;
  
  for(i = j = 0; s[i] != '\0'; i++){
    
    // postfix increment
    if(s[i] != c)
      s[j++] = s[i];

    /* equivalent to
    if(s[i] != c){
      s[j] = s[i];
      ++j;
    }
    */
  }
  s[j] = '\0';
}

void strcat_imp(char s[], char t[]){
  int i, j;

  i = j = 0;
  while(s[i] != '\0') /* find end of s */
    i++;
  while((s[i++] = t[j++]) != '\0'); /* copy t */
}
