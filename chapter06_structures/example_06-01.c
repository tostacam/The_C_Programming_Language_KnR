// 6.1 Basics of Structures

#include <stdio.h>
#include <math.h>

int main(){
  struct point {
    int x;
    int y;
  };

  struct rect {
    struct point pt1;
    struct point pt2;
  };

  struct point pta = {0, 0};
  struct point ptb = {200, 100};
  struct rect screen = {pta, ptb};

  double origin_dist;
  origin_dist = sqrt((double)screen.pt2.x * screen.pt2.x + (double)screen.pt2.y * screen.pt2.y);

  printf("%.4g\n", origin_dist);
}
