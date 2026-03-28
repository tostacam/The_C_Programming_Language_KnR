// 6.7 Typedef

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  
  // typedef on int
  typedef int Length;
  Length len, maxlen;
  Length *lengths[10];

  // typedef on pointer
  typedef char *String;
  String p, lineptr[100], alloc(int);
  p = (String) malloc(100);

  // typedef on struct
  typedef struct tnode *Treeptr;
  typedef struct tnode{
    char *word;
    int count;
    Treeptr left;
    Treeptr right;
  } Treenode;

  // typedef on functions
  typedef int (*PFI)(char *, char *);
}
