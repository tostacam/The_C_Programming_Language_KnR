// Exercise 1.13
// write a program to print a histogram of the lengths of
// words in its input. it is easy to draw the histogram with
// the bars horizontal; a vertical orientation is more challenging

#include <stdio.h>

#define MAXLENGTH 6
#define IN  1
#define OUT 0

int main(){
  int c, i, j, nw, state;
  int nwords[MAXLENGTH];

  state = OUT;
  nw = 0;
  for(i = 0; i < MAXLENGTH; ++i)
    nwords[i] = 0;

  while((c = getchar()) != EOF){
    if(c == ' ' || c == '\n' || c == '\t'){
      ++nwords[nw];
      nw = 0;
      state = OUT;
    }
    else if(state == OUT){
      state = IN;
      ++nw;
    }
    else
      ++nw;
  }

  for(i = 1; i < MAXLENGTH; ++i){
    printf("%d | ", i);
    for(j = 0; j < nwords[i]; j++)
      printf("*");
    printf("\n");
  }
}
