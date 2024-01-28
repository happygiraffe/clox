#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct
{
    Chunk *chunk;
    uint8_t *ip; /* always points to the _next_ instruction to be executed */
    Value stack[STACK_MAX];
    Value *stackTop; /* where to push the next value */
} VM;

typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRE_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
