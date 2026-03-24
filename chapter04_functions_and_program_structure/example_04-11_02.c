// 4.11.2 Macro Substitution

#include <stdio.h>

#define max(A, B) ((A) > (B) ? (A) : (B))
/* max expressions are evaluated twice,
   so this would be wrong
   
   max(i++, j++)
*/

#define square(x) x * x 
/* macro is just text substitution
   
   square(x+1) -> x+1 * x+1 -> x + (1*x) + 1 
   2x + 1 != x * x
*/

int main(){
  int p = 1, q = 2;
  int r = 2, s = 2;
  int x;

  x = max(p+q, r+s);
  printf("max: %d\n", x);

  x = square(x+1);
  printf("square: %d\n", x);
}
