#ifndef LISPSHIT_NODE_H
#define LISPSHIT_NODE_H

#include <ctype.h>

#include "string.h"

struct _Context;

typedef enum _NodeType {
    NODE_NIL,
    NODE_PAIR,
    NODE_INTEGER,
    NODE_SYMBOL,
    NODE_NATIVE_FUNC
} NodeType;


static const uint8_t NP_LITERAL = 0x1u << 0u;
static const uint8_t NP_LIST = 0x1u << 1u;


typedef struct _Node {
    NodeType type;
    uint8_t props;
    union {
        struct {
            struct _Node* left;
            struct _Node* right;
        };
        int32_t integer;
        String symbol;
        struct _Node* (*func)(struct _Context*, struct _Node*);
    };
} Node;


typedef struct _Node*(*NativeFunc)(struct _Context*, struct _Node*);


Node* node_new_nil();
Node* node_new_pair(Node* left, Node* right);
Node* node_new_integer(int32_t integer);
Node* node_new_symbol(String symbol);
Node* node_new_nfunc(NativeFunc func);

uint8_t node_is_list(Node* node);
size_t node_list_length(Node* node);

Node* node_car(Node* node);
Node* node_cdr(Node* node);
Node* node_cons(Node* left, Node* right);

void node_print(Node* node);

#endif //LISPSHIT_NODE_H
