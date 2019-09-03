#include "../headers/gc.h"
#include "../headers/list.h"

#include <malloc.h>

LinkedList nodes = {
        .first=NULL,
        .last=NULL
};

void gc_register(Node* node) {
    linked_list_add(&nodes, node);
}

int gc_node_preserved(Node* node) {
    return node->type == NODE_NATIVE_FUNC
        || node == node_nil()
        || node == node_true()
        || node == node_false();
}

void gc_set_zeroes() {
    LLItem* item = nodes.first;
    while (item != NULL) {
        Node* node = item->value;
        if (gc_node_preserved(node)) {
            node->props |= (uint8_t) NP_GCUSED;
        } else {
            node->props &= (uint8_t) !NP_GCUSED;
        }
        item = item->next;
    }
}

void gc_visit_node(Node* node) {
    if (node->props & NP_GCUSED)
        return;
    node->props |= NP_GCUSED;
    switch (node->type) {
        case NODE_NIL: case NODE_INTEGER:
        case NODE_SYMBOL: case NODE_NATIVE_FUNC:
            break;
        case NODE_FUNC: case NODE_PAIR:
            gc_visit_node(node->left);
            gc_visit_node(node->right);
            break;
    }
}

void gc_visit_ctx(Context* ctx) {
    MapEntry* entry = ctx->variables.first;
    while (entry != NULL) {
        gc_visit_node((Node*) entry->value);
        entry = entry->next;
    }
}

void gc_sweep() {
    LLItem* item = nodes.first;
    if (item == NULL) return;
    while (item != NULL && item->next != NULL) {
        LLItem* next = item->next;
        Node* node = next->value;
        if (!(node->props & NP_GCUSED)) {
            item->next = next->next;
            if (next == nodes.last)
                nodes.last = item;
            free(node);
            free(next);
        }
        item = item->next;
    }
    item = nodes.first;
    Node* node = item->value;
    if (!(node->props & NP_GCUSED)) {
        nodes.first = item->next;
        free(node);
        free(item);
    }
}

void gc_cleanup(Context* ctx) {
    gc_set_zeroes();
    if (ctx != NULL)
        gc_visit_ctx(ctx);
    gc_sweep();
}

void gc_cleanup_all(Context* ctx) {
    LLItem* item = nodes.first;
    while (item != NULL) {
        LLItem* next = item->next;
        free(item->value);
        free(item);
        item = next;
    }
}