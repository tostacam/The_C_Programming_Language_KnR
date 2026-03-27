// Exercise 6.6
// Write a function undef that will remove a name and definition
// from the table maintained by lookup and install.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

#define HASHSIZE  101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *);
char *strdup_imp(char *);
void undef(char *s);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);

int main(){
  struct nlist *np;

  /* insert values */
  install("name", "John");
  install("age", "20");
  install("city", "NY");

  /* overwrite test */
  install("age", "30");

  /* lookup existing */
  if((np = lookup("name")) != NULL)
    printf("name -> %s\n", np->defn);

  if((np = lookup("age")) != NULL)
    printf("age -> %s\n", np->defn);

  if((np = lookup("city")) != NULL)
    printf("city -> %s\n", np->defn);

  /* removing name and definition */
  undef("name");
  if((np = lookup("name")) == NULL)
    printf("name not found\n");

  return 0;
}

/* undef: remove name and definition from hashtab */
void undef(char *s){
  struct nlist *np, *prev;
  unsigned hashval;

  hashval = hash(s);
  np = hashtab[hashval];
  prev = NULL;

  while(np != NULL){
    if(strcmp(s, np->name) == 0){
      if(prev == NULL)
        hashtab[hashval] = np->next;
      else
        prev->next = np->next;

      free(np->name);
      free(np->defn);
      free(np);
      return;
    }
    prev = np;
    np = np-> next;
  }
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

