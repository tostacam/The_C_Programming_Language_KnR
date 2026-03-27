// Exercise 6.2
// Write a program that reads a C program and prints in alphabetical
// order each group of variable names that are identical in the first
// 6 characters, but different somewhere thereafter. Don't count words
// within strings and comments. Make 6 a parameter that can be set from
// the command line.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct tnode {
  char *prefix;
  char **words;
  int count; 
  struct tnode *left; 
  struct tnode *right;
};

struct key {
  char *word;
} keytab[] = {
  {"auto"}, {"break"}, {"case"}, {"char"},
  {"const"}, {"continue"}, {"default"}, {"do"},
  {"double"}, {"else"}, {"enum"}, {"extern"},
  {"float"}, {"for"}, {"goto"}, {"if"},
  {"int"}, {"long"}, {"register"}, {"return"},
  {"short"}, {"signed"}, {"sizeof"}, {"static"},
  {"struct"}, {"switch"}, {"typedef"}, {"union"},
  {"unsigned"}, {"void"}, {"volatile"}, {"while"}
};

#define NKEYS (sizeof(keytab)/sizeof(keytab[0]))

#define MAXWORD 100
#define DEFAULT 6
struct tnode *addtree(struct tnode *, char *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
int binsearch(char *word, struct key tab[], int n);

/* word frequency count */
int main(int argc, char *argv[]){
  struct tnode *root;
  char word[MAXWORD];

  int first_chars = DEFAULT, j;
  char c, num[10];

  /* reading char no. param from command line */
  while(--argc > 0 && (*++argv)[0] == '-'){
    j = 0;
    while(isdigit(c = *++argv[0]))
      num[j++] = c;
    num[j] = '\0';

    first_chars = atoi(num);
  }

  root = NULL; 
  while(getword(word, MAXWORD) != EOF){
    if((isalpha(word[0]) || word[0] == '_') &&
      binsearch(word, keytab, NKEYS) == -1){
  
      char prefix[MAXWORD];
      int len = (first_chars < MAXWORD - 1) ? first_chars : MAXWORD - 1;
      strncpy(prefix, word, len);
      prefix[len] = '\0';

      root = addtree(root, prefix, word);
    }
  }
  
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *strdup_imp(char *);

/* addtree: add a node with w, at ot below p */
struct tnode *addtree(struct tnode *p, char *prefix, char *word){
  int cond;
    
  if(p == NULL){
    p = talloc();
    p->prefix = strdup_imp(prefix);

    p->words = malloc(sizeof(char *));
    p->words[0] = strdup_imp(word);
    p->count = 1;

    p->left = p->right = NULL;
  }
  else if((cond = strcmp(prefix, p->prefix)) == 0){
    // same group → append word
    p->words = realloc(p->words, (p->count + 1) * sizeof(char *));
    p->words[p->count++] = strdup_imp(word);
  }
  else if(cond < 0)
    p->left = addtree(p->left, prefix, word);
  else
    p->right = addtree(p->right, prefix, word);
  
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p){
  if(p != NULL){
    treeprint(p->left);
    if(p->count > 1){
      for(int i = 0; i < p->count; i++)
        printf("%s\n", p->words[i]);
      printf("\n");
    }
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
