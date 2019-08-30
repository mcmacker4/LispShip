#ifndef LISPSHIT_CONTEXT_H
#define LISPSHIT_CONTEXT_H

#include "map.h"
#include "node.h"

typedef struct _Context {
    struct _Context* parent;
    Map variables;
} Context;


Context context_new();

void context_define(Context* ctx, String name, Node* node);

Node* context_get(Context* ctx, String name);

#endif //LISPSHIT_CONTEXT_H
