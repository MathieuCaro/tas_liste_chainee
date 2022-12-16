CC ?= gcc
CFLAGS += -Wall  -g --pedantic -Werror -Wno-error=unused-but-set-variable

LOCAL_LIB=/home/mathieucaro/C/allocation_memo-test/liste_chainee_alloc
LOCAL_INC=/home/mathieucaro/C/allocation_memo-test/liste_chainee_alloc

all:
	$(CC) $(LDFLAGS) -L$(LOCAL_LIB) -I$(LOCAL_INC) -o main $(CFLAGS) fonctions.c main.c -lm -llinkedlist 

test:
	$(CC) $(LDFLAGS) -L$(LOCAL_LIB) -I$(LOCAL_INC) -o test_main $(CFLAGS) tests/test_main.c fonctions.c -lcunit -llinkedlist 

lib:
	make -C $(LOCAL_LIB)

clean:
	rm -f *.o test_main main
