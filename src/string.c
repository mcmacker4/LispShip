#include "../headers/string.h"
#include "../headers/list.h"


List _interns;
int initialized = 0;


String string_intern(const char* str) {
    if (!initialized) {
        _interns = list_new(sizeof(String));
        initialized = 1;
    }

    String* data = ((String*) _interns.data);
    for (int i = 0; i < _interns.size; i++) {
        if (strcmp(data[i], str) == 0) {
            return data[i];
        }
    }

    size_t len = strlen(str);
    char* new = malloc(len + 1);
    strcpy(new, str);
    new[len] = 0;

    list_append(&_interns, &new, sizeof(String));

    return new;
}