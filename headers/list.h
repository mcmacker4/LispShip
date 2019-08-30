#ifndef LISPSHIT_LIST_H
#define LISPSHIT_LIST_H

#include <malloc.h>
#include <mem.h>

#define LIST_INIT_SIZE 4

typedef struct _List {
    void* data;
    int size;
    int capacity;
} List;

void list_free(List* list);

void list_append(List* list, void* value, size_t el_size);

void list_fit(List* list, size_t el_size);

List list_new(size_t el_size);

#endif //LISPSHIT_LIST_H
