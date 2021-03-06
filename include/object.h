#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "chunk.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_NATIVE(value) isObjType(value, OBJ_NATIVE);
#define IS_FUNCTION(value) isObjType(value, OBJ_FUNCTION)
#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_FUNCTION(value) ((ObjFunction *)AS_OBJ(value))
#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)
#define AS_NATIVE(value) (((ObjNative *)AS_OBJ(value))->function)
#define AS_NATIVE_OBJ(value) (((ObjNative *)AS_OBJ(value)))

typedef enum
{
    OBJ_FUNCTION,
    OBJ_NATIVE,
    OBJ_STRING
} ObjType;

struct Obj
{
    ObjType type;
    struct Obj *next;
};

typedef struct
{
    Obj obj;
    int arity;
    Chunk chunk;
    ObjString *name;
} ObjFunction;

typedef Value (*NativeFn)(int argCount, Value *args);

typedef struct
{
    Obj obj;
    NativeFn function;
    const char *name;
} ObjNative;

struct ObjString
{
    Obj obj;
    int length;
    uint32_t hash;
    char chars[];
};

ObjFunction *newFunction();
ObjNative *newNative(NativeFn function, const char *name);
uint32_t hashString(const char *key, int length);
ObjString *internString(ObjString *string);
ObjString *makeString(int length);
ObjString *copyString(const char *chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type)
{
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
