#include "../headers/node.h"

#include "stdio.h"

static Node* nil_node = NULL;

Node* node_new_nil() {
    if (nil_node == NULL) {
        nil_node = malloc(sizeof(Node));
        nil_node->type = NODE_NIL;
        nil_node->integer = 0;
        nil_node->props = 0;
    }
    return nil_node;
}

Node* node_new_pair(Node* left, Node* right) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_PAIR;
    node->left = left;
    node->right = right;
    node->props = 0;
    return node;
}

Node* node_new_integer(int32_t integer) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_INTEGER;
    node->integer = integer;
    node->props = 0;
    return node;
}

Node* node_new_symbol(String symbol) {
    Node* node = malloc(sizeof(Node));
    node->type = NODE_SYMBOL;
    node->symbol = symbol;
    node->props = 0;
    return node;
}

Node* node_new_nfunc(NativeFunc func) {
    Node* node = malloc(sizeof(Node));
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
        iter = iter->right;
    }
    return count;
}


Node* node_car(Node* node) {
    if (node->type == NODE_PAIR)
        return node->left;
    return node_new_nil();
}

Node* node_cdr(Node* node) {
    if (node->type == NODE_PAIR)
        return node->right;
    return node_new_nil();
}

Node* node_cons(Node* left, Node* right) {
    return node_new_pair(left, right);
}

void node_print_list(Node* node) {
    Node* list = node;
    printf("(");
    while (list->right->type != NODE_NIL) {
        node_print(list->left);
        printf(" ");
        list = list->right;
    }
    node_print(list->left);
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
                node_print(node->left);
                printf(" . ");
                node_print(node->right);
                printf(")");
            }
            break;
        }
        case NODE_NATIVE_FUNC:
            printf("native_func");
            break;
    }
}