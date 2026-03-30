// 7.4 Formatted Input-Scanf

#include <stdio.h>

int getline_imp(char *, int lim);

int main(){
  /* reading date input lines */
  int day_, year_;
  char monthname_[20];
  scanf("%d %s %d", &day_, monthname_, &year_);

  /* reading a line at a time and picking it with sscanf */
  int day, month, year;
  char monthname[20], line[100];
  while(getline_imp(line, sizeof(line)) > 0){
    if(sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
      printf("valid: %s\n", line);    /* 25 Dec 1988 form */
    else if(sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
      printf("valid: %s\n", line);    /* mm/dd/yy form */
    else
      printf("invalid: %s\n", line);  /* invalid form */
  }
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
