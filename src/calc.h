#ifndef _CALC_H_
#define _CALC_H_

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define TOL     (1e-10)     /*  tolerance  FIXME */
#define SIZE    (128)       /*  stack size  */

int read_into_stack(STACK s, char *c);
double calc(STACK s);

#endif  /*  calc.h  */
