// Exercise 5.7
// Rewrite readlines to store lines in an array supplied by main,
// rather than calling alloc to maintain storage. How much faster
// is the program?

#include <stdio.h>
#include <string.h>
#define MAXLINES 5000     /* max #lines to be sorted */

char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], char *storage, int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(){
  int nlines;   /* number of input lines read */
  char storage[MAXLINES];

  if((nlines = readlines(lineptr, storage, MAXLINES)) >= 0){
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  }
  else{
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN  1000  /* max length of any input line */
#define MAXMEM  1000
int getline_imp(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], char *storage, int maxlines){
  int len, nlines;
  char *p = storage;
  char *storageEnd = storage + MAXMEM;
  char line[MAXLEN];

  nlines = 0;
  while((len = getline_imp(line, MAXLEN)) > 0)
    if(nlines >= maxlines || p+len > storageEnd)
      return -1;
    else{
      line[len-1] = '\0';   /* delete newline */
      strcpy(p, line);
      lineptr[nlines++] = p;
      p += len;
    }

  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines){
  int i;

  for(i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right){
  int i, last;
  void swap(char *v[], int i, int j);

  if(left >= right)   /* do nothing if array contains */
    return;           /* fewer than two elements */

  swap(v, left, (left + right)/2);

  last = left;
  for(i = left+1; i <= right; i++)
    if(strcmp(v[i], v[left]) < 0)
      swap(v, ++ last, i);

  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

/* swap: intercahgne v[i] and v[j] */
void swap(char *v[], int i, int j){
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
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
