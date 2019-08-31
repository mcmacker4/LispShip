#ifndef LISPSHIT_EVAL_H
#define LISPSHIT_EVAL_H

#include "node.h"
#include "map.h"
#include "context.h"


Node* eval_ctx(Context* ctx, Node* node);
Node* eval(Node* node);

#endif //LISPSHIT_EVAL_H
