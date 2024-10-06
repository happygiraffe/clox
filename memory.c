#include <assert.h>
#include <stdlib.h>

#include "memory.h"
#include "vm.h"

#ifdef DEBUG_LOG_GC
#include <stdio.h>
#include "debug.h"
#endif

void *reallocate(void *pointer, size_t oldSize, size_t newSize)
{
    if (newSize > oldSize)
    {
        // We know we need some more memory so this is a good place to test the
        // GC.
#ifdef DEBUG_STRESS_GC
        collectGarbage();
#endif
    }

    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }
    void *ret = realloc(pointer, newSize);
    assert((ret != NULL));
    return ret;
}

static void freeObject(Obj *object)
{
#ifdef DEBUG_LOG_GC
    printf("%p free type %d\n", (void *)object, object->type);
#endif

    switch (object->type)
    {
    case OBJ_CLOSURE:
    {
        // Only free the closure itself: we don't own the referenced function.
        ObjClosure *closure = (ObjClosure *)object;
        FREE_ARRAY(ObjUpvalue *, closure->upvalues, closure->upvalueCount);
        FREE(ObjClosure, object);
        break;
    }
    case OBJ_FUNCTION:
    {
      ObjFunction *function = (ObjFunction *)object;
      freeChunk(&function->chunk);
      FREE(ObjFunction, function);
      break;
    }
    case OBJ_NATIVE:
        FREE(ObjNative, object);
        break;
    case OBJ_UPVALUE:
        FREE(ObjUpvalue, object);
        // The upvalue does not own the referenced variable.
        break;
    case OBJ_STRING:
    {
        ObjString *string = (ObjString *)object;
        FREE_ARRAY(char, string->chars, string->length + 1);
        FREE(ObjString, object);
        break;
    }
    }
}

void collectGarbage()
{
#ifdef DEBUG_LOG_GC
    printf("-- gc begin\n");
#endif

#ifdef DEBUG_LOG_GC
    printf("-- gc end\n");
#endif
}

void freeObjects()
{
    Obj *object = vm.objects;
    while (object != NULL)
    {
        Obj *next = object->next;
        freeObject(object);
        object = next;
    }
}
