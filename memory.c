#include <assert.h>
#include <stdlib.h>

#include "memory.h"
#include "vm.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize)
{
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
    switch (object->type)
    {
    case OBJ_CLOSURE:
    {
        // Only free the closure itself: we don't own the referenced function.
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
    case OBJ_STRING:
    {
        ObjString *string = (ObjString *)object;
        FREE_ARRAY(char, string->chars, string->length + 1);
        FREE(ObjString, object);
        break;
    }
    }
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
