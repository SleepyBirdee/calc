PROG = calc
CFLAGS = -Wall -pg
LDFLAGS =
LDLIBS = -lm
PROG_OBJS = main.o calc.o stack.o echo_console.o

all: $(PROG)
$(PROG): $(PROG_OBJS)
	$(CC) -Wall $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) -Wall -c $(CFLAGS) $^ -o $@
clean:
	rm -rf $(PROG) *.o *~ *.swp
