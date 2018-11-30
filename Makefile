
EI_GUESS := /usr/lib/erlang/usr/include
GUESS_OK := $(shell bash -c "[[ -d $(EI_GUESS) ]] && echo ok")

ifeq "ok" "$(GUESS_OK)"
	ERLINC := $(EI_GUESS)
else
	ERLINC := $(shell dirname `find /usr -name "erl_nif.h" | head -n 1`)
endif

CFLAGS  := -c -fPIC -I$(ERLINC) -D_GNU_SOURCE
LDFLAGS := -shared

tools.so: src/tools.o
	gcc $(LDFLAGS) -o tools.so src/tools.o $(LDLIBS)

src/tools.o: src/tools.c
	gcc $(CFLAGS) -o src/tools.o src/tools.c

clean:
	rm -f tools.so src/tools.o

.PHONY: clean

