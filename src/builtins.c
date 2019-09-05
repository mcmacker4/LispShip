#include "../headers/builtins.h"
#include "../headers/eval.h"

#include <malloc.h>
#include <stdio.h>
#include <string.h>

Node* builtin_print(Context* ctx, Node* args) {
    if (node_is_list(args)) {
        Node* item = args;
        while (item->type != NODE_NIL) {
            node_print(eval(ctx, node_car(item)));
            item = node_cdr(item);
        }
    } else {
        node_print(args);
    }
    return node_nil();
}

Node* builtin_println(Context* ctx, Node* args) {
    Node* result = builtin_print(ctx, args);
    printf("\n");
    return result;
}

Node* builtin_def(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* name = node_car(args);
        if (name->type == NODE_SYMBOL) {
            if (context_is_defined(ctx, name->symbol)) {
                printf("%s is already defined.\n", name->symbol);
                return node_nil();
            }
            Node* result = eval(ctx, node_car(node_cdr(args)));
            context_define(ctx, name->symbol, result);
            return result;
        } else {
            printf("Invalid arguments.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}

Node* builtin_defun(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) >= 3) {
        Node* name = node_car(args);
        if (name->type == NODE_SYMBOL) {
            if (context_is_defined(ctx, name->symbol)) {
                printf("%s is already defined.\n", name->symbol);
                return node_nil();
            }
            Node* fun = builtin_lambda(ctx, node_cdr(args));
            context_define(ctx, name->symbol, fun);
            return fun;
        } else {
            printf("Invalid arguments.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}

Node* builtin_eval(Context* ctx, Node* args) {
    Node* toeval = eval(ctx, node_car(args));
    return eval_force(ctx, toeval);
}

Node* builtin_lambda(Context* ctx, Node* args) {

    if (node_is_list(args) && node_list_length(args) >= 2) {

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

    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }

}

Node* builtin_apply(Context* ctx, Node* args) {
    Node* arg = args;
    Node* result = node_nil();
    while (arg->type != NODE_NIL) {
        result = eval(ctx, node_car(arg));
        arg = node_cdr(arg);
    }
    return result;
}


Node* builtin_car(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 1) {
        return node_car(eval(ctx, node_car(args)));
    }
    printf("Invalid arguments.\n");
    return node_nil();
}

Node* builtin_cdr(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 1) {
        return node_cdr(eval(ctx, node_car(args)));
    }
    printf("Invalid arguments.\n");
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
        } else if (left->type == NODE_STRING && right->type == NODE_STRING) {
            size_t llen = strlen(left->string);
            size_t rlen = strlen(right->string);
            size_t length = llen + rlen;
            char* buffer = malloc(length + 1);
            strncpy(buffer, left->string, llen);
            strncpy(buffer + llen, right->string, rlen);
            buffer[length] = 0;
            return node_new_string(buffer);
        } else {
            printf("Invalid argument types.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
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
            printf("Invalid argument types.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
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
            printf("Invalid argument types.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
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
            printf("Invalid argument types.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}


Node* builtin_eq(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        switch (left->type) {
            case NODE_NIL:
                return right->type == NODE_NIL ? node_true() : node_false();
            case NODE_PAIR: {
                if (right->type == NODE_PAIR)
                    return left == right ? node_true() : node_false();
                return node_false();
            }
            case NODE_INTEGER: {
                if (right->type == NODE_INTEGER)
                    return left->integer == right->integer ? node_true() : node_false();
                return node_false();
            }
            case NODE_SYMBOL: {
                if (right->type == NODE_SYMBOL)
                    return left->symbol == right->symbol ? node_true() : node_false();
                return node_false();
            }
            case NODE_FUNC: {
                if (right->type == NODE_FUNC)
                    return left == right ? node_true() : node_false();
                return node_false();
            }
            case NODE_NATIVE_FUNC: {
                if (right->type == NODE_NATIVE_FUNC)
                    return left->func == right->func ? node_true() : node_false();
                return node_false();
            }
            case NODE_STRING:
                if (right->type == NODE_STRING)
                    return strcmp(left->string, right->string) == 0 ? node_true() : node_false();
                return node_false();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}

Node* builtin_gt(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        if (left->type == NODE_INTEGER && right->type == NODE_INTEGER) {
            return left->integer > right->integer ? node_true() : node_false();
        } else {
            printf("Invalid argument types.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}

Node* builtin_lt(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 2) {
        Node* left = eval(ctx, node_car(args));
        Node* right = eval(ctx, node_car(node_cdr(args)));
        if (left->type == NODE_INTEGER && right->type == NODE_INTEGER) {
            return left->integer < right->integer ? node_true() : node_false();
        } else {
            printf("Invalid argument types.\n");
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}

// (if (cond) (true) (false))
Node* builtin_if(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 3) {
        Node* cond = node_car(args);
        Node* texpr = node_car(node_cdr(args));
        Node* fexpr = node_car(node_cdr(node_cdr(args)));
        Node* condres = eval(ctx, cond);
        if (condres == node_true()) {
            return eval(ctx, texpr);
        } else {
            return eval(ctx, fexpr);
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}


Node* builtin_len(Context* ctx, Node* args) {
    if (node_is_list(args) && node_list_length(args) == 1) {
        Node* value = eval(ctx, node_car(args));
        if (node_is_list(value)) {
            return node_new_integer(node_list_length(value));
        } else if (value->type == NODE_PAIR) {
            return node_new_integer(2);
        } else if (value->type == NODE_STRING) {
            return node_new_integer(strlen(value->string));
        } else {
            return node_nil();
        }
    } else {
        printf("Invalid number of arguments.\n");
        return node_nil();
    }
}

// substr(str, start, length)
Node* builtin_substr(Context* ctx, Node* args) {
    Node* str = eval(ctx, node_car(args));
    Node* startNode = eval(ctx, node_car(node_cdr(args)));
    Node* lenNode = eval(ctx, node_car(node_cdr(node_cdr(args))));
    if (str->type == NODE_NIL)
        return node_nil();
    if (str->type == NODE_STRING && startNode->type == NODE_INTEGER && (lenNode->type == NODE_INTEGER || lenNode->type == NODE_NIL)) {
        const char* string = str->string;
        int64_t maxlen = strlen(string);
        int64_t start = startNode->integer;
        int64_t length = lenNode->type == NODE_INTEGER ? lenNode->integer : (strlen(string) - start);
        if (length > maxlen) length = maxlen;
        char* buffer = malloc(length + 1);
        strncpy(buffer, string + start, length);
        buffer[length] = 0;
        return node_new_string(buffer);
    } else {
        printf("Invalid arguments.");
        return node_nil();
    }
}