# Just starting...

all: main

OPTS=-Wall -Werror

SRCS=\
	main.c \
	chunk.c \
	memory.c
HDRS=\
	common.h \
	chunk.h \
	memory.h

main: $(SRCS) $(HDRS)
	cc $(OPTS) -o main $(SRCS)
