PROG = calc
CFLAGS = -Wall -g
LDFLAGS =
LDLIBS = -lm
PROG_OBJS = main.o calc.o stack.o echo_console.o

all: $(PROG)
$(PROG): $(PROG_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@
clean:
	rm -rf $(PROG) *.o *~ *.swp
