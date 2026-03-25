// 5.9 Pointers vs Multi-dimensional Arrays

#include <stdio.h>

int main(){
  char *name[] = { "Illegal month", "Jan", "Feb", "Mar" };
  char aname[][15] = { "Illegal month", "Jan", "Feb", "Mar" };

  int size1 = sizeof(name) / sizeof(name[0]);
  int size2 = sizeof(aname) / sizeof(aname[0]);
  
  for(char **p = name; p < name + size1; p++)
    printf("%s\n", *p);

  for(char (*p)[15] = aname; p < aname + size2; p++)
    printf("%s\n", *p);
}
