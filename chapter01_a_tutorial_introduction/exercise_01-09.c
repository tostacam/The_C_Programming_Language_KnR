// Exercise 1.9
// write a program to copy its input to its output,
// replacing each string of one or more blanks by
// a single blank

#include <stdio.h>

int main(){
  int c;
  int blanksFlag = 0;

  while((c = getchar()) != EOF){
    if(c == ' '){
      if(blanksFlag == 0){
        putchar(c);
        blanksFlag = 1;
      }   
    } 
    else {
      putchar(c);
      blanksFlag = 0;  
    }
  }
}
