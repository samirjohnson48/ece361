CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

status: status.o bits.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h bits.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c
	$(CC) $(CFLAGS) -c %<

clean:
	rm -f *.o status
.PHONY: clean
