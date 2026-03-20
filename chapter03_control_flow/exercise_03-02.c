// Exercise 3.2
// write a function escapte(s,t) that converts characters like newline
// and tab into visible escape sequences line \n and \t as it copies the
// string t to s. use a switch. write a function for the other direction
// as well, converting escape sequences into the real characters.

#include <stdio.h>
#define MAXLINE 1000

void escape(char s[], char t[]);
void escape_rev(char s[], char t[]);

int main(){
  char s1[MAXLINE], s2[MAXLINE];
  char t1[] = "hello\tworld\n";
  char t2[] = "hello\\tworld\\n"; 

  escape(s1, t1);
  escape_rev(s2, t2);

  printf("[original string] -> %s\n[escape(s, t)] ->%s\n", t1, s1);
  printf("[original string] -> %s\n[escape_rev(s, t)] ->%s\n", t2, s2);

  return 0;
}

void escape(char s[], char t[]){
  int i = 0, j = 0;
  
  for(i = 0; t[i] != '\0'; ++i){
    switch(t[i]){
      case '\n':
        s[j++] = '\\';
        s[j++] = 'n';
        break;
      case '\t':
        s[j++] = '\\';
        s[j++] = 't';
        break;
      default:
        s[j++] = t[i];
        break;
    }
  }

  s[j] = '\0';
}

void escape_rev(char s[], char t[]){
  int i = 0, j = 0;
  
  for(i = 0; t[i] != '\0'; ++i){
    switch(t[i]){
      case '\\':
        if(t[i+1] == 'n')
          s[j++] = '\n';
        if(t[i+1] == 't')
          s[j++] = '\t';
        ++i;
        break;
      default:
        s[j++] = t[i];
        break;
    }
  }

  s[j] = '\0';
}
