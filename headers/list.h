#ifndef LISPSHIT_LIST_H
#define LISPSHIT_LIST_H

#include <stddef.h>

#define LIST_INIT_SIZE 4

// Adjacent memory list

typedef struct _List {
    void* data;
    int size;
    int capacity;
} List;

void list_free(List* list);

void list_append(List* list, void* value, size_t el_size);

void list_fit(List* list, size_t el_size);

List list_new(size_t el_size);

// Linked list

typedef struct _LLItem {
    void* value;
    struct _LLItem* next;
} LLItem;

typedef struct _LinkedList {
    LLItem* first;
    LLItem* last;
} LinkedList;

LinkedList linked_list_new();

void linked_list_add(LinkedList* list, void* value);



#endif //LISPSHIT_LIST_H
