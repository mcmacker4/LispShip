#include "../headers/eval.h"
#include "../headers/context.h"
#include "../headers/builtins.h"

#include <stdio.h>


Context eval_context_new() {
    Context ctx = context_new(NULL);

#define CTX_DEF(ctx, name, func)\
    context_define((ctx), string_intern(name), node_new_nfunc(func))

    CTX_DEF(&ctx, "print", &builtin_print);
    CTX_DEF(&ctx, "println", &builtin_println);
    CTX_DEF(&ctx, "def!", &builtin_def);
    CTX_DEF(&ctx, "car", &builtin_car);
    CTX_DEF(&ctx, "cdr", &builtin_cdr);
    CTX_DEF(&ctx, "cons", &builtin_cons);
    CTX_DEF(&ctx, "+", &builtin_plus);
    CTX_DEF(&ctx, "-", &builtin_minus);
    CTX_DEF(&ctx, "*", &builtin_times);
    CTX_DEF(&ctx, "/", &builtin_div);

#undef CTX_DEF

    return ctx;
}

Node* eval_funcall(Context* ctx, Node* node) {
    Node* name = node->left;
    Node* args = node->right;
    if (name->type == NODE_SYMBOL) {
        Node* func = context_get(ctx, name->symbol);
        if (func == NULL) {
            printf("Unable to resolve symbol: %s\n", name->symbol);
            return node_new_nil();
        } else {
            if (func->type == NODE_NATIVE_FUNC) {
                return func->func(ctx, args);
            } else {
                printf("How the hell?\n");
                return node_new_nil();
            }
        }
    } else {
        printf("Syntax error in funcall. (%d)\n", name->type);
        return node_new_nil();
    }
}

Node* eval_ctx(Context* ctx, Node* node) {
    if (node->props & NP_LITERAL) {
        return node;
    } else {
        switch (node->type) {
            case NODE_NIL:
            case NODE_INTEGER:
            case NODE_NATIVE_FUNC:
                return node;
            case NODE_SYMBOL:
                return context_get(ctx, node->symbol);
            case NODE_PAIR:
                return eval_funcall(ctx, node);
        }
    }
}

Node* eval(Node* node) {
    Context ctx = eval_context_new();
    return eval_ctx(&ctx, node);
}