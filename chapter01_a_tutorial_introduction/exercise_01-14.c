// Exercise 1.14
// write a program to print a histogram of the frequencies
// of different characters in its input

#include <stdio.h>

#define CHARS 256

int main(){
  int c, i, j;
  int charFreq[CHARS];

  for(i = 0; i < CHARS; i++)
    charFreq[i] = 0;

  while((c = getchar()) != EOF){
    if(c != '\n' && c != ' ')
      ++charFreq[c];
  }

  for(i = 0; i < CHARS; ++i){
    if(charFreq[i] != 0){
      printf("%c | ", i);
      for(j = 0; j < charFreq[i]; j++){
        printf("*");
      }
      printf("\n");
    }
  }
}
