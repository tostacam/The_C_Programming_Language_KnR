// 3.2 If-Else

#include <stdio.h>

int function(void);

int main(){
  int a = 0, b = 10, n = 5, z;
  
  // else associated to the closest previous if
  if(n > 0)
    if(a > b)
      z = a;
    else 
      z = b;

  // use curly brackets to avoid ambiguity
  if (n > 0){
    if(a > b)
      z = a;
  }
  else
    z = b;
}

int function(){
  int n = 10, i;
  int s[20];

  // ambiguity can be pernicious in situations as such:
  if(n >= 0)
    for(i = 0; i < n; ++i)
      if(s[i] > 0){
        printf("...");
        return i;
      }
   else /* WRONG: dangling else -> warning produced by compiler */
     printf("error -- n is negative\n");
}
