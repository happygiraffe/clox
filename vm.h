#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

typedef struct VM
{
    Chunk *chunk;
    uint8_t *ip; /* always points to the _next_ instruction to be executed */
    Value stack[STACK_MAX];
    Value *stackTop; /* where to push the next value */
    Obj *objects;
} VM;

typedef enum InterpretResult
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm; // access to global shared state 🤮

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
