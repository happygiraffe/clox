# Just starting...

all: clox

CC=clang++-16
OPTS=-std=c++20 -Wall -Werror

SRCS=\
	main.cc \
	chunk.cc \
	compiler.cc \
	debug.cc \
	memory.cc \
	object.cc \
	scanner.cc \
	table.cc \
	value.cc \
	vm.cc
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
	$(CC) $(OPTS) -o $@ $(SRCS)

clean:
	rm -f clox
