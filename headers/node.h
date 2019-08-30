#ifndef LISPSHIT_NODE_H
#define LISPSHIT_NODE_H

#include <ctype.h>

#include "string.h"

typedef enum _NodeType {
    NODE_NIL,
    NODE_PAIR,
    NODE_INTEGER,
    NODE_SYMBOL
} NodeType;

typedef struct _Node {
    NodeType type;
    union {
        struct {
            struct _Node* left;
            struct _Node* right;
        };
        int32_t integer;
        String symbol;
    };
} Node;

#endif //LISPSHIT_NODE_H
