#ifndef LISPSHIT_MAP_H
#define LISPSHIT_MAP_H

#include "string.h"

typedef struct _MapEntry {
    String key;
    void* value;
} MapEntry;

typedef struct _Map {
    MapEntry* entries;
    size_t size;
    size_t capacity;
} Map;

Map map_new();

void* map_get(Map* map, String key);

void map_put(Map* map, String key, void* value);

#endif //LISPSHIT_MAP_H
