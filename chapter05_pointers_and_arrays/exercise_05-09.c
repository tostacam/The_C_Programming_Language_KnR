// Exercise 5.9
// Rewrite the routines day_of_year and month_day with
// pointers instead of indexing.

#include <stdio.h>

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day){
  int leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  
  char *p = *(daytab + leap);
  
  for( ; p < *(daytab + leap) + month; p++)
    day += *p;
  return day;
}

/* month_day: set monmth, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday){
  int leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  char *p = *(daytab + leap);

  for( ; yearday > *p; p++)
    yearday -= *p;
  *pmonth = p - *(daytab + leap);
  *pday = yearday;
}

int main(){
  printf("(2023, Mar 1): %d\n", day_of_year(2023, 3, 1));
  printf("(2024, Mar 1): %d\n", day_of_year(2024, 3, 1));

  int month, day;

  month_day(2023, 60, &month, &day);
  printf("(2023, day 60): %d/%d\n", month, day);
  month_day(2024, 61, &month, &day);
  printf("(2024, day 61): %d/%d\n", month, day);
}
