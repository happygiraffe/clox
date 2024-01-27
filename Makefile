# Just starting...

all: main

OPTS=-Wall -Werror

SRCS=\
	main.c \
	debug.c \
	chunk.c \
	memory.c
HDRS=\
	debug.h \
	common.h \
	chunk.h \
	memory.h

main: $(SRCS) $(HDRS)
	cc $(OPTS) -o main $(SRCS)
