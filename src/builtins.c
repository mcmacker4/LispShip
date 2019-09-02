#include "../headers/builtins.h"
#include "../headers/eval.h"
#include "../headers/node.h"

#include <stdio.h>

Node* builtin_print(Context* context, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 1) {
        node_print(eval(context, args->left));
    } else {
        printf("Invalid argument.");
    }
    return node_nil();
}

Node* builtin_println(Context* context, Node* args) {
    Node* result = builtin_print(context, args);
    printf("\n");
    return result;
}

Node* builtin_def(Context* context, Node* args) {
    Node* name = node_car(args);
    if (name->type == NODE_SYMBOL) {
        Node* result = eval(context, node_car(node_cdr(args)));
        context_define(context, name->symbol, result);
        return result;
    } else {
        printf("Invalid arguments.\n");
        return node_nil();
    }
}

Node* builtin_eval(Context* context, Node* args) {
    Node* toeval = eval(context, node_car(args));
    return eval_force(context, toeval);
}

Node* builtin_lambda(Context* context, Node* args) {

    Node* fnargs = node_car(args);

    // Check that fnargs is a list of symbols
    Node* arg = fnargs;
    while (node_car(arg)->type != NODE_NIL) {
        if (node_car(arg)->type != NODE_SYMBOL) {
            printf("Syntax error in lambda arguments.\n");
            return node_nil();
        }
        arg = node_cdr(arg);
    }

    Node* body = node_cdr(args);
    if (!node_is_list(body)) {
        printf("Syntax error in lambda body.\n");
        return node_nil();
    }

    return node_new_func(fnargs, body);

}



Node* builtin_car(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 1) {
        return node_car(eval(ctx, args->left));
    }
    printf("Invalid arguments.");
    return node_nil();
}

Node* builtin_cdr(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 1) {
        return node_cdr(eval(ctx, args->left));
    }
    printf("Invalid arguments.");
    return node_nil();
}

Node* builtin_cons(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        return node_cons(left, right);
    } else {
        printf("Invalid arguments.\n");
        return node_nil();
    }
}

Node* builtin_plus(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        if (left->type == NODE_INTEGER && right->type == NODE_INTEGER) {
            return node_new_integer(left->integer + right->integer);
        } else {
            printf("Invalid argument types.");
        }
    } else {
        printf("Invalid number of arguments.");
        return node_nil();
    }
}

Node* builtin_minus(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        if (left->type == NODE_INTEGER && right->type == NODE_INTEGER) {
            return node_new_integer(left->integer - right->integer);
        } else {
            printf("Invalid argument types.");
        }
    } else {
        printf("Invalid number of arguments.");
        return node_nil();
    }
}

Node* builtin_times(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        if (left->type == NODE_INTEGER && right->type == NODE_INTEGER) {
            return node_new_integer(left->integer * right->integer);
        } else {
            printf("Invalid argument types.");
        }
    } else {
        printf("Invalid number of arguments.");
        return node_nil();
    }
}

Node* builtin_div(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        if (left->type == NODE_INTEGER && right->type == NODE_INTEGER) {
            return node_new_integer(left->integer / right->integer);
        } else {
            printf("Invalid argument types.");
        }
    } else {
        printf("Invalid number of arguments.");
        return node_nil();
    }
}
