#ifndef LISPSHIT_EVAL_H
#define LISPSHIT_EVAL_H

#include "node.h"
#include "map.h"
#include "context.h"

Context eval_context_new();

Node* eval_force(Context* ctx, Node* node);
Node* eval(Context* ctx, Node* node);

#endif //LISPSHIT_EVAL_H
