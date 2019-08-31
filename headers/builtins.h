#ifndef LISPSHIT_BUILTINS_H
#define LISPSHIT_BUILTINS_H

#include "node.h"
#include "context.h"

Node* builtin_print(Context* context, Node* args);
Node* builtin_println(Context* context, Node* args);
Node* builtin_def(Context* context, Node* args);

Node* builtin_car(Context* ctx, Node* args);
Node* builtin_cdr(Context* ctx, Node* args);
Node* builtin_cons(Context* ctx, Node* args);

Node* builtin_plus(Context* ctx, Node* args);
Node* builtin_minus(Context* ctx, Node* args);
Node* builtin_times(Context* ctx, Node* args);
Node* builtin_div(Context* ctx, Node* args);

#endif //LISPSHIT_BUILTINS_H
