#ifndef LISPSHIT_EVAL_H
#define LISPSHIT_EVAL_H

#include "node.h"
#include "map.h"
#include "context.h"

Context eval_context_new();

Node* eval(Context* ctx, Node* node);

#endif //LISPSHIT_EVAL_H
