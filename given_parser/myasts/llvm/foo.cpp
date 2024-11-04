/* 
 * Nakul Nayak
 * CPE 453
 * Description: 
 */

/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <string>

/* macros, if any */

/* function prototypes */

/* global vars, if any */
int x;
int y;
typedef struct Shape Shape;
struct Shape{
    int num_sides;
    char *name;
    int num;
    Shape *sh;
    bool b;
};

/* main function */
int main ()
{
    //int x;
    Shape *s = (Shape *)malloc(sizeof(Shape));;
    s->num = 5;
    //Shape *s;
    //s->sh->num = 3;
    return 98;
}

void temp() {
}
int foo(int a, int b, int c)
{
  int ret = 0;

  if(a)
  {
    ret = 1;
    if(b)
    {
      ret = 2;
      if(c)
      {
        ret = 3;
      }
    }
  }

  return ret;
}

void blue() {
    int x=5;
}
