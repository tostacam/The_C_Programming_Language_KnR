// 6.8 Unions

#include <stdio.h>

#define NSYM    100
#define INT     0
#define FLOAT   1
#define STRING  2

int main(){
  union u_tag {
    int ival;
    float fval;
    char *sval;
  } u;

  int utype = FLOAT;
  u.fval = 1.2f;

  if(utype == INT)
    printf("%d\n", u.ival);
  else if(utype == FLOAT)
    printf("%f\n", u.fval);
  else if(utype == STRING)
    printf("%s\n", u.sval);
  else
    printf("bad type %d in utype\n", utype);
  
  struct {
    char *name;
    int flags;
    int utype;
    union {
      int ival;
      float fval;
      char *sval;
    } u;
  } symtab[NSYM]; // union int member referred to as:
                  //   symtab[i].u.ival
                  // 
                  // union char* member referred to as:  
                  //   *symtab[i].u.sval
                  //   symtab[i].u.sval[0]
}
