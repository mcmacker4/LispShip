#ifndef LISPSHIT_MAP_H
#define LISPSHIT_MAP_H

#include "string.h"

typedef struct _MapEntry {
    String key;
    void* value;
    struct _MapEntry* next;
} MapEntry;

typedef struct _Map {
    MapEntry* first;
    MapEntry* last;
} Map;

Map map_new();

void* map_get(Map* map, String key);
int map_contains_key(Map* map, String key);

void map_put(Map* map, String key, void* value);

void map_free(Map* map);

#endif //LISPSHIT_MAP_H
