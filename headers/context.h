#ifndef LISPSHIT_CONTEXT_H
#define LISPSHIT_CONTEXT_H

#include "map.h"

struct _Node;

typedef struct _Context {
    struct _Context* parent;
    Map variables;
} Context;


Context context_new(Context* parent);

void context_define(Context* ctx, String name, struct _Node* node);

struct _Node* context_get(Context* ctx, String name);

#endif //LISPSHIT_CONTEXT_H
