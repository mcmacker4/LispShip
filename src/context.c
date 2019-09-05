#include "../headers/context.h"
#include "../headers/node.h"

Context context_new(Context* parent) {
    Context context;
    context.variables = map_new();
    context.parent = parent;
    return context;
}

void context_define(Context* ctx, String name, struct _Node* node) {
    map_put(&ctx->variables, name, node);
}

int context_is_defined(Context* ctx, String name) {
    return map_contains_key(&ctx->variables, name);
}

struct _Node* context_get(Context* ctx, String name) {
    void* result = map_get(&ctx->variables, name);
    if (result == NULL) {
        if (ctx->parent != NULL) {
            return context_get(ctx->parent, name);
        } else {
            return node_nil();
        }
    }
    return (struct _Node*) result;
}

void context_destroy(Context* ctx) {
    map_free(&ctx->variables);
}