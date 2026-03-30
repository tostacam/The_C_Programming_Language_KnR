// Exercise 7.7
// Modify the pattern finding program of Chapter 5 (5.10) to take its
// input from a set of named files or, if no files are named as arguments,
// from the standard input. Should the file name be printed when a matching
// line is found?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

int getline_imp(char *line, int max);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]){
  char line[MAXLINE];
  long lineno = 0;
  int c, except = 0, number = 0, found = 0;

  FILE *fp;
  char *prog = argv[0];
  
  while(--argc > 0 && (*++argv)[0] == '-')
    while((c = *++argv[0]))
      switch(c){
      case 'x':
        except = 1;
        break;
      case 'n':
        number = 1;
        break;
      default:
        printf("find: illegal option %c\n", c);
        argc = 0;
        found = -1;
        break;
      }

  if(argc < 1){
    printf("Usage: find -x -n pattern\n");
    exit(1);
  }

  char *pattern;
  pattern = strdup(*argv++);

  if(argc > 1){
    while(--argc > 0){
      if((fp = fopen(*argv, "r")) == NULL){
        fprintf(stderr, "%s: can't open %s", prog, *argv);
        exit(2);
      }
      printf("Looking in File: [%s]\n", *argv);

      lineno = 0;
      while(fgets(line, MAXLINE, fp) != NULL){
        ++lineno;
        if((strstr(line, pattern) != NULL) != except){
          if(number)
            printf("%ld:", lineno);
          printf("%s", line);
        }
        ++found;
      }
      ++argv;
    }
  }
  else {
    while(fgets(line, MAXLINE, stdin) != NULL){
      ++lineno;
      if((strstr(line, pattern) != NULL) != except){
        if(number)
          printf("%ld:", lineno);
        printf("%s", line);
        ++found;
      }
    }
  }

  /*
  if(argc <= 1)
    printf("Usage: find -x -n pattern\n");
  else{

    

    while(--argc > 0){
      if((fp = fopen(*++argv, "r")) == NULL){
        printf("find: can't open %s\n", *argv);
        exit(1);
      }
      lineno = 0;
      while(fgets(line, MAXLINE, fp) != NULL)
        lineno++;
        if((strstr(line, *argv)))
    }
  }
  */
/*  
     while(getline_imp(line, MAXLINE) > 0){
      lineno++;
      if((strstr(line, *argv) != NULL) != except){
        if(number)
          printf("%ld:", lineno);
        printf("%s", line);
        found++;
      }
    }
*/
  return found;
}

int getline_imp(char *line, int lim){
  int c, i;

  for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;

  if(c == '\n'){
    line[i] = c;
    ++i;
  }
  line[i] = '\0';

  return i;
}
