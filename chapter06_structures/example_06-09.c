// 6.9 Bit-fields

#include <stdio.h>

#define KEYWORD   01
#define EXTERNAL  02
#define STATIC    04
enum { KEYWORD_ = 01, EXTERNAL_ = 02, STATIC_ = 04 };

int main(){
  // Bit flag (Idiom)
  int flags;
  
  // turn bit on
  flags |= EXTERNAL | STATIC;

  // turn bit off
  flags &= ~(EXTERNAL | STATIC);

  // conditional check for multiple bits (off)
  if((flags & (EXTERNAL | STATIC)) == 0)
    printf("both flags are off!\n");

  // Bit flag (Bit-field)
  struct {
    unsigned int is_keyword : 1;
    unsigned int is_extern  : 1;
    unsigned int is_static  : 1;
  } flags_;

  // turn bits on
  flags_.is_extern = flags_.is_static = 1;

  // turn bits off
  flags_.is_extern = flags_.is_static = 0;

  // condidiontal check for multiple bits (off)
  if(flags_.is_extern == 0 && flags_.is_static == 0)
    printf("both flags are off!\n");
}
