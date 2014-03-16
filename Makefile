LIBEVENT=libevent
OBJS_EVT=event.o
CC=gcc
AR=ar
CFLAGS=-Werror -Wall -pedantic

ifeq ($(CONFIG_DEBUG),y)
	CFLAGS+=-g -O0
else
	CFLAGS+=-O2
endif

OBJS=event.o

libevent: $(OBJS_EVT)
	$(AR) -r $@.a $^

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -rf *.o *.a

cleanall: clean
	rm -rf tags
