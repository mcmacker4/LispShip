#include "string.h"
#include "list.h"


List* _interns = NULL;


String string_intern(const char* str) {
    if (_interns == NULL) {
        _interns = malloc(sizeof(List));
        *_interns = list_new(sizeof(String));
    }

    for (int i = 0; i < _interns->size; i++) {
        if (strcmp(((const char**) _interns->data)[i], str) == 0) {
            return ((String) _interns->data) + i;
        }
    }

    size_t len = strlen(str);
    char* new = malloc(len + 1);
    strcpy(new, str);
    new[len] = 0;

    list_append(_interns, &new, sizeof(char*));

    return new;
}