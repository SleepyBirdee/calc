#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

bool is_empty(STACK s)
{
    if (NULL == s) {
        ECHO_CONSOLE_ERR("stack is NULL");
        return false;
    }

    return (s->tos == EMPTY_TOS);
}

bool is_full(STACK s)
{
    if (NULL == s) {
        ECHO_CONSOLE_ERR("stack is NULL");
        return false;
    }

    return (s->tos == s->capacity);
}

STACK create_stack(int max_elements)
{
    STACK s = NULL;

    if (max_elements < MIN_STACK_SIZE) {
        ECHO_CONSOLE_ERR("designated max_elements is too small, default is used!");
        max_elements = MIN_STACK_SIZE;
    }
    
    s = (STACK)calloc(sizeof(STACK_RECORD), 1);
    if (NULL == s) {
        ECHO_CONSOLE_ERR("malloc error!");
        return NULL;   /*  or exit(-1) */
    }
    
    s->array = (ELEMENT_TYPE *)calloc(sizeof(ELEMENT_TYPE) * max_elements, 1);
    if (NULL == s->array) {
        ECHO_CONSOLE_ERR("malloc error!");
        free(s);
        return NULL;
    }

    s->capacity = max_elements;
    make_empty(s);

    return s;
}   /*  create_stack    */

void dispose_stack(STACK s)
{
    if (NULL == s) {
        ECHO_CONSOLE_ERR("NULL stack.");
        return;
    }

    free(s->array);
    s->array = NULL;
    free(s);
    s = NULL;
}   /*  dispose_stack   */

void make_empty(STACK s)
{
    int i = 0;
    ELEMENT_TYPE element = ZERO_ELEMENT;

    if (NULL == s) {
        ECHO_CONSOLE_ERR("stack is NULL, create one first!");
        return;
    }

    s->tos = EMPTY_TOS;
    for (i = 0; i < s->capacity; i ++) {
        s->array[i] = element;  /*  () [] -> . associativity: left to right  */
    }
}   /*  make_empty  */

void push(ELEMENT_TYPE x, STACK s)
{
    if (NULL == s || is_full(s)) {
        ECHO_CONSOLE_ERR("cannot push!\n");
        ECHO_CONSOLE_ERR("check if stack is NULL or is already full!");
        exit(-1);
    }

    s->array[++ s->tos] = x;
}   /*  push    */

void pop(STACK s)
{
    ELEMENT_TYPE element = ZERO_ELEMENT;
    if (NULL == s || is_empty(s)) {
        ECHO_CONSOLE_ERR("cannot pop!");
        ECHO_CONSOLE_ERR("check if stack is NULL or is empty!");
        exit(-1);
    }

    s->array[s->tos --] = element;
}   /*  pos */

ELEMENT_TYPE top(STACK s)
{
    ELEMENT_TYPE element = ZERO_ELEMENT;
    if (NULL == s || is_empty(s)) {
        ECHO_CONSOLE_ERR("cannot top!");
        ECHO_CONSOLE_ERR("check if stack is NULL or is empty!");
        return element;
    }

    return s->array[s->tos];
}   /*  top */

ELEMENT_TYPE top_and_pop(STACK s)
{
    if (NULL == s || is_empty(s)) {
        ECHO_CONSOLE_ERR("cannot top_and_pop!");
        ECHO_CONSOLE_ERR("check if stack is NULL or is empty!");
        exit(-1);
    }

    return s->array[s->tos --];
}   /*  top_and_pop */

#if 0
void print_stack(char *msg, STACK s) /*    WARNING: this function will make stack empty!   */
{
    if (NULL == s) {
        ECHO_CONSOLE_ERR("cannot print_stack!");
        ECHO_CONSOLE_ERR("check if stack is NULL or is empty!");
        return;
    }

    ELEMENT_TYPE element = ZERO_ELEMENT;
    while (!is_empty(s)) {
        element = top_and_pop(s);
        ECHO_CONSOLE_DEBUG("%s: element.type = %d", msg, element.type);
        if (element.type == TYPE_NUM) {
            ECHO_CONSOLE_DEBUG("%s: element.value.num = %lf", msg, element.value.num);
        } else if (element.type == TYPE_OP) {
            ECHO_CONSOLE_DEBUG("%s:element.value.op = %c", msg, element.value.op);
        } else {
            ECHO_CONSOLE_ERR("%s: internal error!", msg);
            return;
        }
    }
}   /*  print_stack */
#endif

void print_stack(char *msg, STACK s)
{
    if (NULL == s) {
        ECHO_CONSOLE_ERR("cannot print_stack!");
        ECHO_CONSOLE_ERR("check if stack is NULL or is empty!");
        return;
    }
    
    int tmp_tos = s->tos;
    ELEMENT_TYPE element = ZERO_ELEMENT;
    
    while (tmp_tos >= 0) {
        element = s->array[tmp_tos --];

//      ECHO_CONSOLE_DEBUG("%s: element.type = %d", msg, element.type);
        if (element.type == TYPE_NUM) {
            ECHO_CONSOLE_DEBUG("%s: element.value.num = %lf", msg, element.value.num);
        } else if (element.type == TYPE_OP) {
            ECHO_CONSOLE_DEBUG("%s: element.value.op = %c", msg, element.value.op);
        } else {
            ECHO_CONSOLE_ERR("%s: internal error!", msg);
            return;
        }
    }
}   /*  print_stack */
