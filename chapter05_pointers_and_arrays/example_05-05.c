// 5.5 Character Pointers and Functions

#include <stdio.h>

/* strcpy: copy t to s; array subscript version */
void strcpy_subscript(char *s, char *t){
  int i;

  i = 0;
  while((s[i] = t[i]) != '\0')
    i++;
}

/* strcpy: copy t to s; pointer version 1 */
void strcpy_pointer1(char *s, char *t){
  while((*s = *t) != '\0'){
    s++;
    t++;  
  }
}

/* strcpy: copy t to s; pointer version 2 */
void strcpy_pointer2(char *s, char *t){
  while((*s++ = *t++) != '\0');
}

/* strcpy: copy t to s; pointer version 3 */
void strcpy_pointer3(char *s, char *t){
  while((*s++ = *t++));
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_subscript(char *s, char *t){
  int i;

  for(i = 0; s[i] == t[i]; i++)
    if(s[i] == '\0')
      return 0;

  return s[i] - t[i];
}

/* strcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp_pointer(char *s, char *t){
  for(; *s == *t; s++, t++)
    if(*s == '\0')
      return 0;
  return *s - *t;
}

int main(){
  return 0;
}
