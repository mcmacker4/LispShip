#include "../headers/node.h"
#include "../headers/list.h"
#include "../headers/gc.h"

#include <stdio.h>
#include <malloc.h>

static Node* nil = NULL;
static Node* true = NULL;
static Node* false = NULL;


Node* node_new() {
    Node* node = malloc(sizeof(Node));
    gc_register(node);
    return node;
}

Node* node_nil() {
    if (nil == NULL) {
        nil = node_new();
        nil->type = NODE_NIL;
        nil->integer = 0;
        nil->props = NP_LIST;
    }
    return nil;
}

Node* node_true() {
    if (true == NULL) {
        true = node_new();
        true->type = NODE_SYMBOL;
        true->symbol = string_intern("true");
        true->props = 0;
    }
    return true;
}

Node* node_false() {
    if (false == NULL) {
        false = node_new();
        false->type = NODE_SYMBOL;
        false->symbol = string_intern("false");
        false->props = 0;
    }
    return false;
}

Node* node_new_pair(Node* left, Node* right) {
    Node* node = node_new();
    node->type = NODE_PAIR;
    node->left = left;
    node->right = right;
    node->props = 0;
    return node;
}

Node* node_new_integer(int32_t integer) {
    Node* node = node_new();
    node->type = NODE_INTEGER;
    node->integer = integer;
    node->props = 0;
    return node;
}

Node* node_new_string(const char* string) {
    Node* node = node_new();
    node->type = NODE_STRING;
    node->string = string;
    node->props = 0;
    return node;
}

Node* node_new_symbol(String symbol) {
    if (symbol == string_intern("nil")) {
        return node_nil();
    } else if (symbol == string_intern("true")) {
        return node_true();
    } else if (symbol == string_intern("false")) {
        return node_false();
    } else {
        Node* node = node_new();
        node->type = NODE_SYMBOL;
        node->symbol = symbol;
        node->props = 0;
        return node;
    }
}

Node* node_new_func(Node* args, Node* body) {
    Node* node = node_new();
    node->type = NODE_FUNC;
    node->left = args;
    node->right = body;
    node->props = NP_LIST;
    return node;
}

Node* node_new_nfunc(NativeFunc func) {
    Node* node = node_new();
    node->type = NODE_NATIVE_FUNC;
    node->func = func;
    node->props = 0;
    return node;
}


uint8_t node_is_list(Node* node) {
    return node->props & NP_LIST;
}

size_t node_list_length(Node* node) {
    Node* iter = node;
    size_t count = 0;
    while (iter->type != NODE_NIL) {
        count++;
        iter = node_cdr(iter);
    }
    return count;
}


Node* node_car(Node* node) {
    if (node->type == NODE_PAIR || node->type == NODE_FUNC)
        return node->left;
    return node_nil();
}

Node* node_cdr(Node* node) {
    if (node->type == NODE_PAIR || node->type == NODE_FUNC)
        return node->right;
    return node_nil();
}

Node* node_cons(Node* left, Node* right) {
    return node_new_pair(left, right);
}

void node_print_list(Node* node) {
    Node* list = node;
    printf("(");
    while (node_cdr(list)->type != NODE_NIL) {
        node_print(node_car(list));
        printf(" ");
        list = node_cdr(list);
    }
    node_print(node_car(list));
    printf(")");
}

void node_print(Node* node) {
    switch (node->type) {
        case NODE_NIL:
            printf("nil");
            break;
        case NODE_INTEGER:
            printf("%d", node->integer);
            break;
        case NODE_SYMBOL:
            printf("%s", node->symbol);
            break;
        case NODE_PAIR: {
            if (node->props & NP_LIST) {
                node_print_list(node);
            } else {
                printf("(");
                node_print(node_car(node));
                printf(" . ");
                node_print(node_cdr(node));
                printf(")");
            }
            break;
        }
        case NODE_NATIVE_FUNC:
            printf("native_func");
            break;
        case NODE_FUNC:
            printf("func");
            break;
        case NODE_STRING:
            printf("%s", node->string);
            break;
    }
}


void node_cleanup() {
    free(nil);
    free(true);
    free(false);
}