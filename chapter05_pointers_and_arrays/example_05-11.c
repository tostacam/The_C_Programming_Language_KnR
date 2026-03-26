// 5.11 Pointers to Functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES  5000    /* max #lines to be sorted */
#define MAXLEN    1000
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int getline_imp(char s[], int lim);
char *alloc(int n);

void qsort_imp(void *lineptr[], int left, int right, int (*comp)(const void *, const void *));
int numcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[]){
  int nlines;   /* number of input lines read */
  int numeric = 0;

  if(argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  if((nlines = readlines(lineptr, MAXLINES)) >= 0){
    qsort_imp((void **) lineptr, 0, nlines-1, (int (*)(const void*, const void*))(numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort_imp(void *v[], int left, int right, int (*comp)(const void *, const void *)){
  int i, last;
  void swap(void *v[], int, int);

  if(left >= right)   /* do nothing if array contains */
    return;           /* fewer than two elements */
  swap(v, left, (left+right)/2);
  last = left;
  for(i = left+1; i <= right; i++)
    if((*comp)(v[i], v[left]) < 0)
      swap(v, ++last, i);
  
  swap(v, left, last);
  qsort_imp(v, left, last-1, comp);
  qsort_imp(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2){
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if(v1 < v2)
    return -1;
  else if(v1 > v2)
    return 1;
  else 
    return 0;
}

/* void swap */
void swap(void *v[], int i, int j){
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines){
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while((len = getline_imp(line, MAXLEN)) > 0)
    if(nlines >= maxlines || (p = alloc(len)) == NULL)
      return -1;
    else{
      line[len-1] = '\0';   /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
    }

  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines){
  int i;

  for(i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* getline: read a line into s, return length */
int getline_imp(char s[], int lim){
  int c, i;

  for(i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if(c == '\n'){
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

#define ALLOCSIZE 1000  /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free position */

/* return pointer to n characters */
char *alloc(int n){
  if(allocbuf + ALLOCSIZE - allocp >= n){  /* it fits */
    allocp += n;
    return allocp - n;    /* old p */
  }
  else                    /* not enough room */
    return 0;
}
