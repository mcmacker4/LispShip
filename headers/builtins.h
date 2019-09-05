#ifndef LISPSHIT_BUILTINS_H
#define LISPSHIT_BUILTINS_H

#include "node.h"
#include "context.h"

Node* builtin_print(Context* ctx, Node* args);
Node* builtin_println(Context* ctx, Node* args);
Node* builtin_def(Context* ctx, Node* args);
Node* builtin_defun(Context* ctx, Node* args);
Node* builtin_eval(Context* ctx, Node* args);
Node* builtin_lambda(Context* ctx, Node* args);
Node* builtin_apply(Context* ctx, Node* args);

Node* builtin_car(Context* ctx, Node* args);
Node* builtin_cdr(Context* ctx, Node* args);
Node* builtin_cons(Context* ctx, Node* args);

Node* builtin_plus(Context* ctx, Node* args);
Node* builtin_minus(Context* ctx, Node* args);
Node* builtin_times(Context* ctx, Node* args);
Node* builtin_div(Context* ctx, Node* args);

Node* builtin_eq(Context* ctx, Node* args);
Node* builtin_gt(Context* ctx, Node* args);
Node* builtin_lt(Context* ctx, Node* args);

Node* builtin_if(Context* ctx, Node* args);

Node* builtin_len(Context* ctx, Node* args);
Node* builtin_substr(Context* ctx, Node* args);

#endif //LISPSHIT_BUILTINS_H
