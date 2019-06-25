#include "calc.h"
#include <math.h>
#include <string.h>
#include <errno.h>

static bool isop(int c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^');
}
#if 0
void push_num_to_stack(STACK s, ELEMENT_TYPE x)
{
    if (x.type != TYPE_NUM) {
        ECHO_CONSOLE_ERR("to push a non-num to stack!\n");
        return;
    }

    push(x, s);
}


void push_op_to_stack(STACK s, ELEMENT_TYPE x)
{
    if (x.type != TYPE_OP) {
        ECHO_CONSOLE_ERR("to push a non-op ti stack!\n");
        return;
    }

    push(x, s);
}
#endif

static int op_level(int op) {
    if (!isop(op)) {
        ECHO_CONSOLE_ERR("%d is not an operator!", op);
        return -1;
    }

    switch (op) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case ')':
            return 4;
        default:
            return -1;
    }
}

int read_into_stack(STACK s, char *c)
{
    if (NULL == s) {
        ECHO_CONSOLE_ERR("stack is NULL, create_stack() first!");
        return -1;
    }
    if (NULL == c) {
        ECHO_CONSOLE_ERR("input string is NULL!");
        return -1;
    }

    double value = 0.0;
    char *str = c;
    int need_op = 0;
    char *endptr = c;
    errno = 0;
    STACK tmp_s = create_stack(s->capacity);

    if (NULL == tmp_s) {
        ECHO_CONSOLE_ERR("creat_stack error!");
        return -1;
    }  
    ELEMENT_TYPE element = ZERO_ELEMENT;
    element.type = TYPE_NUM;
    element.value.num = 0;
    push(element, s);

    while (*endptr != '\0') {
        if (!need_op) {
            value = strtod(str, &endptr);
            if ((errno == ERANGE && (value == HUGE_VALF || value == HUGE_VALL))  /* overflow FIXME   */
            || (errno == ERANGE && (value - 0) * (value - 0) < TOL * TOL)) {    /*  underflow FIXME  */
                ECHO_CONSOLE_ERR("strtod error : %s", strerror(errno));
                goto err_quit;
            }
        }
        need_op = 0;
        if (endptr != str) {  /* conversion performed (a number is read in) */
            element.type = TYPE_NUM;
            element.value.num = value;

            push(element, s);    /* push number to stack */
        }
        
        while (*endptr == '\040')  /*  ignore space    */
            endptr ++;

        if (*endptr != '\0') {
            if (!isop(*endptr)) {         /*MUST BE AN OPERATOR or is an invalid expression */
                ECHO_CONSOLE_ERR("*endptr is not an operator.");
                goto err_quit;
            }

            element.type = TYPE_OP;
            element.value.op = *endptr ++;
            ECHO_CONSOLE_DEBUG("element.value.op = %c", element.value.op);

            /* * 
             * push operator to stack 
             */
            
            switch (op_level(element.value.op)) {
                case 0:     /*  '('     */
                    break;
                case 1:     /*  '+', '-'    */
                    while (!is_empty(tmp_s) && op_level(top(tmp_s).value.op) >= 1) {
                        push(top_and_pop(tmp_s), s);
                    }
                    break;
                case 2:     /*  '*', '/'    */
                    while (!is_empty(tmp_s) && op_level(top(tmp_s).value.op) >= 2) {
                        push(top_and_pop(tmp_s), s);
                    }
                    break;
                case 3:     /*  '^' */
                    while (!is_empty(tmp_s) && op_level(top(tmp_s).value.op) > 3) {
                        push(top_and_pop(tmp_s), s);
                    }
                    break;
                case 4:     /*  ')'    */
                    if (element.value.op == ')') {
                        while (!is_empty(tmp_s) && op_level(top(tmp_s).value.op) < 4 && op_level(top(tmp_s).value.op) != 0) {
                            push(top_and_pop(tmp_s), s);
                        }
                        if (top(tmp_s).value.op != '(') {
                            ECHO_CONSOLE_ERR("error: '(' and ')' don't match!!");
                            goto err_quit;
                        }
                        pop(tmp_s); /*  pop up '(' */
                    }
                    break;
                default:
                    goto err_quit;
            }

            if (element.value.op != ')') {
                push(element, tmp_s);
            } else {
                need_op = 1;
            }
        }
        str = endptr;
    }

    while (!is_empty(tmp_s)) {
        push(top_and_pop(tmp_s), s);
    }

    ECHO_CONSOLE_DEBUG("read_into_stack success!");
    dispose_stack(tmp_s);
    return 0;
err_quit:
    dispose_stack(tmp_s);
    return -1;
}   /*  read_into_stack */

static double eval(double a, int op, double b)
{
    ECHO_CONSOLE_DEBUG("a = %lf\top = %c\tb = %lf", a, op, b);
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if ((b - 0) * (b - 0) < TOL * TOL) {
                ECHO_CONSOLE_ERR("devided by zero! exit!!!!");
                exit(-1);
            }
            return a / b;
        case '^':
            return pow(a,b);
        default :
            ECHO_CONSOLE_ERR("internal error, exit!");
            exit(-1);
    }
}   /*  eval    */

double calc(STACK s)
{
    ELEMENT_TYPE tmp_element1 = ZERO_ELEMENT;
    ELEMENT_TYPE tmp_element2 = ZERO_ELEMENT;
    ELEMENT_TYPE tmp_element3 = ZERO_ELEMENT;
    

    if (NULL == s || is_empty(s)) {
        ECHO_CONSOLE_ERR("can't eval empty (or NULL) stack!");
        return -1;
    }

    STACK tmp_s = create_stack(s->capacity);
    if (NULL == tmp_s) {
        ECHO_CONSOLE_ERR("create_stack() error!");
        return -1;
    }

    while (!is_empty(s)) {  /*  reverse stack   */
        push(top_and_pop(s), tmp_s);
    }
    while (!is_empty(tmp_s)) {
        tmp_element1 = top_and_pop(tmp_s);
        
        if (tmp_element1.type == TYPE_NUM) {
            push(tmp_element1, s);
        } else if (tmp_element1.type == TYPE_OP) {
            tmp_element2 = top_and_pop(s);
            tmp_element3 = top_and_pop(s);

            if (tmp_element2.type != TYPE_NUM || tmp_element3.type != TYPE_NUM) {
                ECHO_CONSOLE_ERR("internal error!");
                dispose_stack(tmp_s);
                return -1;
            }

            tmp_element2.value.num = eval(tmp_element3.value.num, tmp_element1.value.op, tmp_element2.value.num);
            push(tmp_element2, s);
        } else {
            ECHO_CONSOLE_ERR("internal error!");
            dispose_stack(tmp_s);
            return -1;
        }
    }
    dispose_stack(tmp_s);
    
    tmp_element1 = top_and_pop(s);
    if (tmp_element1.type != TYPE_NUM) {
        printf(".type = %d\t.value.num = %lf\n", tmp_element1.type, tmp_element1.value.num);
        ECHO_CONSOLE_ERR("internal error!");
        return -1;
    }
    
    if (!is_empty(s)) {
        if (top(s).type != TYPE_NUM && (top(s).value.num - 0) * (top(s).value.num - 0) > TOL * TOL) {
            printf(".type = %d\t.value.num = %lf\n", top(s).type, top(s).value.num);
            printf("internal error!\n");
            return -1;
        }       
    }
    return (tmp_element1.value.num);
}   /*  calc    */
