# Just starting...

all: clox

# TODO: reenable -Werror
OPTS=-Wall # -Werror

SRCS=\
	main.c \
	chunk.c \
	compiler.c \
	debug.c \
	memory.c \
	scanner.c \
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
	value.h \
	vm.h

clox: $(SRCS) $(HDRS)
	cc $(OPTS) -o $@ $(SRCS)
