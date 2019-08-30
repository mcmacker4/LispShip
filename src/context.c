#include "../headers/context.h"


Context context_new() {
    Context context;
    context.variables = map_new();
    return context;
}

void context_define(Context* ctx, String name, Node* node) {
    map_put(&ctx->variables, name, node);
}

Node* context_get(Context* ctx, String name) {
    return (Node*) map_get(&ctx->variables, name);
}