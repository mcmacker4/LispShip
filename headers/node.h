#ifndef LISPSHIT_NODE_H
#define LISPSHIT_NODE_H

#include <stdint.h>
#include <stddef.h>

#include "string.h"

struct _Context;

typedef enum _NodeType {
    NODE_NIL,
    NODE_PAIR,
    NODE_INTEGER,
    NODE_SYMBOL,
    NODE_STRING,
    NODE_FUNC,
    NODE_NATIVE_FUNC,
} NodeType;


#define NP_LITERAL (0x1u << 0u)
#define NP_LIST (0x1u << 1u)
#define NP_GCUSED (0x1u << 7u)


typedef struct _Node {
    NodeType type;
    uint8_t props;
    union {
        struct { // NODE_PAIR | NODE_FUNC
            struct _Node* left;
            struct _Node* right;
        };
        int32_t integer; // NODE_INTEGER
        String symbol; // NODE_SYMBOL
        const char* string;
        struct _Node* (*func)(struct _Context*, struct _Node*); // NODE_NATIVE_FUNC
    };
} Node;


typedef struct _Node*(*NativeFunc)(struct _Context*, struct _Node*);


Node* node_nil();
Node* node_true();
Node* node_false();
Node* node_new_pair(Node* left, Node* right);
Node* node_new_integer(int32_t integer);
Node* node_new_string(const char* string);
Node* node_new_symbol(String symbol);
Node* node_new_func(Node* args, Node* body);
Node* node_new_nfunc(NativeFunc func);

uint8_t node_is_list(Node* node);
size_t node_list_length(Node* node);

Node* node_car(Node* node);
Node* node_cdr(Node* node);
Node* node_cons(Node* left, Node* right);

void node_print(Node* node);

void node_cleanup();

#endif //LISPSHIT_NODE_H
