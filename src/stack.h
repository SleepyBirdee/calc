#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include "echo_console.h"

#define EMPTY_TOS       (-1)    /*  empty top of stack  */
#define MIN_STACK_SIZE  (8)
#define ZERO_ELEMENT    {.type = 0, .value.op = 0}        /*  for initialization ONLY */

#define TYPE_NONE       (0)
#define TYPE_NUM        (1)
#define TYPE_OP         (2)

typedef struct {
    unsigned int type;
    union {
        unsigned int    op;
        double          num;
    } value;
} ELEMENT_TYPE;

typedef struct _STACK_RECORD {
    int capacity;
    int tos;    /*  Top Of Stack    */
    ELEMENT_TYPE *array;
} STACK_RECORD;
typedef STACK_RECORD *STACK;

/**********************************  
 *  functions prototypes          *
 **********************************/
bool is_empty(STACK s);
bool is_full(STACK s);
STACK create_stack(int max_elements);
void dispose_stack(STACK s);
void make_empty(STACK s);
void push(ELEMENT_TYPE x, STACK s);
void pop(STACK s);  /*  !! NO RETURN VALUE !!*/
ELEMENT_TYPE top(STACK s);
ELEMENT_TYPE top_and_pop(STACK s);
void print_stack(char *msg, STACK s);  /* ONLY for debug   */
#endif /*   stack.h */
