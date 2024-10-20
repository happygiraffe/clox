# Just starting...

all: clox

OPTS=-Wall -Werror

SRCS=\
	main.c \
	chunk.c \
	compiler.c \
	debug.c \
	memory.c \
	object.c \
	scanner.c \
	table.c \
	value.c \
	vm.c
HDRS=\
	chunk.h \
	common.h \
	compiler.h \
	debug.h \
	memory.h \
	object.h \
	scanner.h \
	table.h \
	value.h \
	vm.h

clox: $(SRCS) $(HDRS)
	c++ $(OPTS) -o $@ $(SRCS)

clean:
	rm -f clox
