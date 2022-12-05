CC ?= gcc
CFLAGS += -Wall --pedantic -Werror -Wno-error=unused-but-set-variable

all:
	$(CC) $(LDFLAGS) -o main $(CFLAGS) fonctions.c main.c -lm

test:
	$(CC) $(LDFLAGS)  -o test_main $(CFLAGS) tests/test_main.c fonctions.c -lcunit

clean:
	rm -f *.o test_main main
