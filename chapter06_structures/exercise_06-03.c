// Exercise 6.3
// Write a cross-referencer that prints a list of all words in a document,
// and, for each word, a list of the line numbers on which it occurs.
// Remove noise words like "the", "and", and so on.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXCOUNT  10

struct tnode {
  char *word;
  int lineCount;
  int level[MAXCOUNT]; 
  struct tnode *left; 
  struct tnode *right;
};

struct key {
  char *word;
} keytab[] = {
  {"and"}, {"is"}, {"so"}, {"that"}, {"the"}
};

#define NKEYS (sizeof(keytab)/sizeof(keytab[0]))

#define MAXWORD 100
struct tnode *addtree(struct tnode *, int, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *word, struct key tab[], int n);

/* word frequency count */
int main(int argc, char *argv[]){
  struct tnode *root;
  char word[MAXWORD];
  int line_level = 1;

  root = NULL; 
  while(getword(word, MAXWORD) != EOF){
    if(word[0] == '\n')
      ++line_level;
    if((isalpha(word[0]) || word[0] == '_') &&
      binsearch(word, keytab, NKEYS) == -1){
      root = addtree(root, line_level, word);
    }
  }

  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *strdup_imp(char *);

/* addtree: add a node with w, at ot below p */
struct tnode *addtree(struct tnode *p, int level, char *word){
  int cond, i = 0;
    
  if(p == NULL){
    p = talloc();
    p->word = strdup_imp(word);
    p->lineCount = 0;
    p->level[p->lineCount++] = level;
    p->left = p->right = NULL;
  }
  else if((cond = strcmp(word, p->word)) == 0){
    if(p->level[p->lineCount-1] != level)
      p->level[p->lineCount++] = level;
  }
  else if(cond < 0)
    p->left = addtree(p->left, level, word);
  else
    p->right = addtree(p->right, level, word);
  
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p){
  if(p != NULL){
    treeprint(p->left);
    printf("%s: ", p->word);
    for(int i = 0; i < p->lineCount; i++)
      printf("%d ", p->level[i]);
    printf("\n");
    treeprint(p->right);
  }
}

/* talloc: make a tnode */
struct tnode *talloc(void){
  return (struct tnode*) malloc(sizeof(struct tnode));
}

/* strdup: make a duplicate of s */
char *strdup_imp(char *s){
  char *p;

  p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
  if(p != NULL)
    strcpy(p, s);
  return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim){
  int c, cNext, getch(void);
  void ungetch(int);
  char *w = word;

  while((c = getch()) == ' ');
  if(c == EOF)
    return EOF;
  
  if(c == '/'){
    cNext = getch();
    if(cNext == '*'){
      while(1){
        if((c = getch()) == '*'){
          if((c = getch()) == '/')
            break;
          else
            ungetch(c);
        }
      }
      return getword(word, lim);
    }
    else if(cNext == '/'){
      while((c = getch()) != '\n' && c != EOF);
      return getword(word, lim);
    }
    else
      ungetch(cNext);
  }

  if(c == '"'){
    while((c = getch()) != '"' && c != EOF);
    return getword(word, lim);
  }

  *w++ = c;
  *w = '\0';

  if(!isalpha(c) && c != '_'){
    *w = '\0';
    return c;
  }
  for(; --lim > 0; w++)
    if(!isalnum(*w = getch())){
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

#define BUFSIZE 100

char buf [BUFSIZE]; /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void ungetch(int c){
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n){
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while(low <= high){
    mid = (low + high)/2;
    if((cond = strcmp(word, tab[mid].word)) < 0)
      high = mid - 1;
    else if(cond > 0)
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}
