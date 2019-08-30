#include "../headers/list.h"

void _list_grow(List* list, size_t el_size) {
    int newcap = list->capacity * 3 / 2;
    list->data = realloc(list->data, newcap * el_size);
    list->capacity = newcap;
}

void list_free(List* list) {
    free(list->data);
    list->data = NULL;
}

void list_append(List* list, void* value, size_t el_size) {
    if (list->size == list->capacity)
        _list_grow(list, el_size);
    void* dst = list->data + list->size * el_size;
    memcpy(dst, value, el_size);
    list->size++;
}

void list_fit(List* list, size_t el_size) {
    realloc(list->data, list->size * el_size);
    list->capacity = list->size;
}

List list_new(size_t el_size) {
    List list;
    list.size = 0;
    list.capacity = LIST_INIT_SIZE;
    list.data = malloc(LIST_INIT_SIZE * el_size);
    return list;
}