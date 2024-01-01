#include <stdlib.h>

typedef struct Point
{
  int x, y;
  int inclusive;
} Point;

typedef struct Line
{
  Point *start, end;
} Line;
