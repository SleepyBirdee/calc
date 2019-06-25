#include "calc.h"

void usage(char *s)
{
    ECHO_CONSOLE_ERR("usage: %s <expressions>", s);
}


int main(int argc, char **argv)
{
    if (argc == 1) {
        usage(argv[0]);
        return -1;
    }

    int i = 0, err = 0;
    ssize_t n = 0;
    double res = 0;
    STACK s = NULL;
    char exps[SIZE + 1] = {0};

    while (NULL != argv[++ i]) {
        n += snprintf(exps + n, SIZE + 1, "%s", argv[i]);
        ECHO_CONSOLE_DEBUG("%s", exps);
    }

    s = create_stack(SIZE);
    if (NULL == s) {
        ECHO_CONSOLE_ERR("create_stack() error!");
        return -1;
    }
    err = read_into_stack(s, exps);
    if (err == -1) {
        ECHO_CONSOLE_ERR("read_into_stack error!");
        return -1;
    }
    
    res = calc(s);
    ECHO_CONSOLE_ERR("%s = %lf", exps, res);

    dispose_stack(s);
    
    return 0;
}
