status: status.o bits.o
	gcc -std=c11 -Wall -Wextra -o status status.o bits.o

status.o: status.c status.h bits.h
	gcc -std=c11 -Wall -Wextra -c status.c

bits: bits.o
	gcc -std=c11 -Wall -Wextra -o bits bits.o

bits.o: bits.c bits.h
	gcc -std=c11 -Wall -Wextra -c bits.c

