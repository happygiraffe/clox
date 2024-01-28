#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl()
{
    char line[1024];
    for (;;)
    {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
        {
            printf("\n");
            break;
        }
        interpret(line);
    }
}

static char *readFile(const char *path)
{
    FILE *fh = fopen(path, "rb");
    if (fh == NULL)
    {
        fprintf(stderr, "Could not open \"%s\": %s", path, strerror(errno));
        exit(74);
    }
    fseek(fh, 0L, SEEK_END);
    size_t fileSize = ftell(fh);
    rewind(fh);

    char *buffer = (char *)malloc(fileSize + 1);
    if (buffer == NULL)
    {
        fprintf(stderr, "out of memory\n");
        exit(74);
    }
    size_t bytesRead = fread(buffer, sizeof(char), fileSize, fh);
    if (bytesRead < fileSize)
    {
        fprintf(stderr, "Could not read \"%s\": %s", path, strerror(errno));
        exit(74);
    }
    buffer[bytesRead] = '\0';

    fclose(fh);
    return buffer;
}

static void runFile(const char *path)
{
    char *source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR)
        exit(65);
    if (result == INTERPRE_RUNTIME_ERROR)
        exit(70);
}

int main(int argc, const char *argv[])
{
    initVM();

    if (argc == 1)
    {
        repl();
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        fprintf(stderr, "usage: clox [path]\n");
    }

    freeVM();
    return 0;
}
