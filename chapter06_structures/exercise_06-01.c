// Exercise 6.1
// Our version of getword does not properly handle underscores, string
// constants, comments, or preprocessor control lines. Write a better
// version.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key{
  char* word;
  int count;
} keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "for", 0,
  "if", 0,
  "int", 0,
  "return", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main(){
  int n;
  char word[MAXWORD];

  while(getword(word, MAXWORD) != EOF)
    if(isalpha(word[0]))
      if((n = binsearch(word, keytab, NKEYS)) >= 0)
        keytab[n].count++;
      
  for(n = 0; n < NKEYS; n++)
    if(keytab[n].count > 0)
      printf("%4d %s\n", keytab[n].count, keytab[n].word);

  return 0;
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

#define MAXVAL  100 /* maximum depth of val stack */
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
