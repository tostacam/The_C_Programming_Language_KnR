// Exercise 2.3
// write the function htoi(s), which converts a string of
// hexadecimal digits (including an optional 0x or 0X) into 
// its equivalent integer value. The allowable digits are 0
// through 9, a through f, and A through F;

#include <stdio.h>

int htoi(char s[]);
void lower(char s[]);

int main(){
  char hex1[] = "1A";
  char hex2[] = "0x1A";
  char hex3[] = "0xFF";
  char hex4[] = "0xFa3";

  lower(hex1);
  lower(hex2);
  lower(hex3);
  lower(hex4);
  printf("hex %s to int: %d\n", hex1, htoi(hex1)); 
  printf("hex %s to int: %d\n", hex2, htoi(hex2)); 
  printf("hexx %s to int: %d\n", hex3, htoi(hex3)); 
  printf("hex %s to int: %d\n", hex4, htoi(hex4)); 
}

int htoi(char s[]){
  int i = 0, n = 0;
  
  while(s[i] != '\0'){
    if(s[i] == '0' && s[i+1] != '\0' && s[i+1] == 'x')
      ++i;
    else
      if('a' <= s[i] && s[i] <= 'f')
        n = n * 16 + (10 + s[i] - 'a');
      else
        n = n * 16 + (s[i] - '0');
    ++i;
  }

  return n;
}

void lower(char s[]){
  int i = 0;

  while(s[i] != '\0'){
    if('A' <= s[i] && s[i] <= 'Z')
      s[i] = s[i] + 'a' - 'A';      
    ++i;
  }
}
