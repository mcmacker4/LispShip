#ifndef LISPSHIT_GC_H
#define LISPSHIT_GC_H

#include "../headers/context.h"
#include "../headers/node.h"

void gc_register(Node* node);

void gc_cleanup(Context* ctx);
void gc_cleanup_all();

#endif //LISPSHIT_GC_H
