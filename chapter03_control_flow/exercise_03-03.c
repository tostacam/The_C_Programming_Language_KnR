// Exercise 3.6
// write a function expand(s1,s2) that expands shorthand notations
// like a-z in the string s1 into the equivalent complete list abc...xyz
// in s2. allow for letters of either case and digits, and be prepared
// to handle cases like a-b-c and a-z0-9 and -a-z. arrange that a leading
// or trailing - is taken literally/

#include <stdio.h>
#define MAXLINE 1000

int is_valid_char(char c);
void expand(char s1[], char s2[]);

int main(){
  char s1[] = "a-b-c0-9", s2[MAXLINE]; 
  char s3[] = "a-z0-9", s4[MAXLINE]; 
  char s5[] = "-A-D-", s6[MAXLINE]; 

  expand(s1, s2);
  expand(s3, s4);
  expand(s5, s6);

  printf("%s -> expanded -> %s\n", s1, s2);
  printf("%s -> expanded -> %s\n", s3, s4);
  printf("%s -> expanded -> %s\n", s5, s6);
}

/* note: not testing for invalid ranges, i.e., a-9 */
int is_valid_char(char c){
  if(('a' <= c && c <= 'z')
    || ('A' <= c && c <= 'Z')
    || ('0' <= c && c <= '9')){
    return 1; 
  }
  return 0;
}

void expand(char s1[], char s2[]){
  int i = 0, j = 0, k = 0;

  while(s1[i] != '\0'){
    if(s1[i] == '-'){
      if( (i-1 >= 0) && is_valid_char(s1[i-1])
        && (s1[i+1] != '\0') && is_valid_char(s1[i+1]) ){
        
        j = i + 2;
        while(s1[j] != '\0' && s1[j+1] != '\0'){
          if(s1[j] == '-' && is_valid_char(s1[j+1]))
            j += 2;
          else
            break;
        }

        for(int t = s1[i-1] + 1; t <= s1[j-1]; ++t)
          s2[k++] = t;

        i = j;
      }
      else{
        s2[k++] = '-';
        ++i;
      }   
    }
    else{
      s2[k++] = s1[i++];
    }
  }

  s2[k] = '\0';
}
