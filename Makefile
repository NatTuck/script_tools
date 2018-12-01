
EI_GUESS := /usr/lib/erlang/usr/include
GUESS_OK := $(shell bash -c "[[ -d $(EI_GUESS) ]] && echo ok")

ifeq "ok" "$(GUESS_OK)"
	ERLINC := $(EI_GUESS)
else
	ERLINC := $(shell dirname `find /usr -name "erl_nif.h" | head -n 1`)
endif

CFLAGS  := -c -fPIC -I$(ERLINC) -D_GNU_SOURCE
LDFLAGS := -shared

priv/script_tools.so: src/script_tools.o
	mkdir -p priv
	gcc $(LDFLAGS) -o priv/script_tools.so src/script_tools.o $(LDLIBS)

src/script_tools.o: src/script_tools.c
	gcc $(CFLAGS) -o src/script_tools.o src/script_tools.c

clean:
	rm -f priv/*.so src/*.o

.PHONY: clean

