#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"

typedef struct Entry
{
    ObjString *key;
    Value value;
} Entry;

typedef struct Table
{
    int count;
    int capacity;
    Entry *entries;
} Table;

void initTable(Table *table);
void freeTable(Table *table);
bool tableGet(Table *table, ObjString *key, Value *value);
bool tableSet(Table *table, ObjString *key, Value value);
bool tableDelete(Table *table, ObjString *key);
void tableAddAll(Table *from, Table *to);
ObjString *tableFindString(Table *table, const char *chars, int length, uint32_t hash);

#endif // clox_table_h
