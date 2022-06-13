#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type *)allocateObject(sizeof(type), objectType)

static Obj *allocateObject(size_t size, ObjType type)
{
    Obj *object = (Obj *)reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;
    return object;
}

uint32_t hashString(const char *key, int length)
{
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++)
    {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
}

ObjString *internString(ObjString *string)
{
    ObjString *interned = tableFindString(&vm.strings, string->chars,
                                          string->length, string->hash);

    if (interned != NULL)
    {
        return interned;
    }
    else
    {
        tableSet(&vm.strings, string, NIL_VAL);
        return string;
    }
}

ObjString *makeString(int length)
{
    ObjString *string = (ObjString *)allocateObject(
        sizeof(ObjString) + length + 1, OBJ_STRING);
    string->length = length;
    return string;
}

ObjString *copyString(const char *chars, int length)
{
    ObjString *interned = tableFindString(&vm.strings, chars,
                                          length, hashString(chars, length));

    if (interned != NULL)
    {
        return interned;
    }
    ObjString *string = makeString(length);

    memcpy(string->chars, chars, length);
    string->chars[length] = '\0';
    string->hash = hashString(chars, length);
    tableSet(&vm.strings, string, NIL_VAL);
    return string;
}

void printObject(Value value)
{
    switch (OBJ_TYPE(value))
    {
    case OBJ_STRING:
    {
#ifdef DEBUG_TRACE_EXECUTION
        printf("\"%s\"", AS_CSTRING(value));
#endif
#ifndef DEBUG_TRACE_EXECUTION
        printf("%s", AS_CSTRING(value));
#endif
        break;
    }
    }
}