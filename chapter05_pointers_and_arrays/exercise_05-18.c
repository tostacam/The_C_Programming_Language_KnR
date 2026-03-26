// Exercise 5.18
// Make dcl recover fromm input errors.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;            /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];           /* output string */

/* convert declaration to words */
int main(){
  while(gettoken() != EOF){   /* 1st token on line */
    strcpy(datatype, token);  /* is the data type */
    out[0] = '\0';
    dcl();                    /* parse rest of line */
    if(tokentype != '\n'){
      printf("syntax error\n");
      while(tokentype != '\n' && tokentype != EOF)
        tokentype = gettoken();
    }
    printf("%s: %s %s\n", name, out, datatype);
  }
}

/* dcl: parse a declarator */
void dcl(){
  int ns;

  for(ns = 0; gettoken() == '*'; )  /* count *'s */
    ns++;
  dirdcl();
  while(ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void){
  int type;

  if(tokentype == '('){         /* ( dcl ) */
    dcl();
    if(tokentype != ')'){
      printf("error: missing )\n");
    
      while(tokentype != '\n' && tokentype != EOF)
        tokentype = gettoken();

      return;
    }
  } 
  else if (tokentype == NAME)   /* variable name */
    strcpy(name, token);
  else{
    printf("error: expected name of (dcl)\n");

    while(tokentype != '\n' && tokentype != EOF)
      tokentype = gettoken();

    return; 
  }
  while((type = gettoken()) == PARENS || type == BRACKETS)
    if(type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

/* gettoken: return next token */
int gettoken(void){
  int c, getch(void);
  void ungetch(int);
  char *p = token;

  while((c = getch()) == ' ' || c == '\t');

  if(c == '\n')
    return tokentype = '\n';

  if(c == '(') {
    if((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } 
    else {
     ungetch(c);
     return tokentype = '(';
    }
  } 
  else if(c == '['){
    for(*p++ = c; (*p++ = getch()) != ']'; );
    *p = '\0';
    return tokentype = BRACKETS;
  } 
  else if(isalpha(c)){
    for(*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }

  /* fall back as recovery */
  token[0] = c;
  token[1] = '\0';
  return tokentype = c;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/* get a (possibly pushed back) character */
int getch(void){
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void ungetch(int c){
  if(bufp >= BUFSIZE)
    printf("ungetch: too many characters");
  else
    buf[bufp++] = c;
}
