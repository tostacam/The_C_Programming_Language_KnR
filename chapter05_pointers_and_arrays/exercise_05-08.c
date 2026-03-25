// Exercise 5.8
// There is no error checking in day_of_year or month_day.
// Remedy this defect.

#include <stdio.h>

static char daytab[2][13] = {
  {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day){
  int i, leap;

  if(month > 12 || month < 1)
    return -1;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

  if(day > daytab[leap][month] || day < 0)
    return -1;

  for(i = 1; i < month; i++)
    day += daytab[leap][i];
  return day;
}

/* month_day: set monmth, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday){
  int i, leap;

  leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
  
  if(yearday < 1){
    *pmonth = -1;
    *pday = -1;
    return;
  }

  if(leap){
    if(yearday > 366){
      *pmonth = -1;
      *pday = -1;
      return;
    }
  }
  else{
    if(yearday > 365){
      *pmonth = -1;
      *pday = -1;
      return;
    }
  }

  for(i = 1; yearday > daytab[leap][i]; i++)
    yearday -= daytab[leap][i];
  *pmonth = i;
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

  // testing for errors
  printf("(2023, 0 10) expecting error: %d\n", day_of_year(2023, 0, 10));
  printf("(2023, 13 10) expecting error: %d\n", day_of_year(2023, 13, 10));
  printf("(2023, 2 30) expecting error: %d\n", day_of_year(2023, 2, 30));

  month_day(2023, 0, &month, &day);
  printf("(2023, day 0) expecting error: %d/%d\n", month, day);
  month_day(2023, 366, &month, &day);
  printf("(2023, day 366) expecting error: %d/%d\n", month, day);
}
