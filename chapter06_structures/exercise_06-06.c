// Exercise 6.6
// Implement a simple version of the #define processor (i.e., no arguments)
// suitable for use with C programs, based on the routines of this section.
// Youe may also find gethc and ungetch helpful.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

#define OUT       0
#define IN        1
#define MAXWORD   100
#define HASHSIZE  101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

int getword(char *, int);
int getch(void);
void ungetch(int);
unsigned hash(char *);
char *strdup_imp(char *);
void undef(char *s);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);

int main(){
  struct nlist *np;
  char word[MAXWORD];

  char *define_name, *define_value;
  int define_status = OUT;
  while(getword(word, MAXWORD) != EOF){
    if(!define_status){
      if(strcmp(word, "#define") == 0){
        define_status = IN;
        continue;
      }
      if((np = lookup(word)) != NULL)
        printf("%s ", np->defn);
      else
        printf("%s ", word);
    }
    else{
      if(word[0] == '\n'){
        install(define_name, define_value);
        define_status = OUT;
        continue;
      }
      if(isalpha(word[0]))
        define_name = strdup_imp(word);
      else
        define_value = strdup_imp(word);
    }
  }

  return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s){
  unsigned hashval;

  for(hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;

  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s){
  struct nlist *np;

  for(np = hashtab[hash(s)]; np != NULL; np = np->next)
    if(strcmp(s, np->name) == 0)
      return np;  /* found */
  return NULL;    /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn){
  struct nlist *np;
  unsigned hashval;

  if((np = lookup(name)) == NULL){  /* not found */
    np = (struct nlist *) malloc(sizeof(*np));
    if(np == NULL || (np->name = strdup_imp(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  }
  else                        /* already there */
    free((void *) np->defn);  /* free previous defn */

  if((np->defn = strdup_imp(defn)) == NULL)
    return NULL;

  return np;
}

/* strdup_imp: make a duplicate of s */
char *strdup_imp(char *s){
  char *p;

  p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
  if(p != NULL)
    strcpy(p, s);
  return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim){
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while((c = getch()) == ' ' || c == '\t');

  if(c != EOF)
    *w++ = c;
  if(!isalpha(c) && (c != '#') && !isdigit(c)){
    *w = '\0';
    return c;
  }
  for(; --lim > 0; w++)
    if(!isalpha(*w = getch()) && !isdigit(*w) && (*w != '.')){
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
