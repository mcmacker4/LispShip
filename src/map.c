#include "../headers/map.h"

#define MAP_CAPACITY 5

void map_grow(Map* map) {
    size_t newcap = map->capacity * 3 / 2;
    map->entries = realloc(map->entries, newcap * sizeof(MapEntry));
    map->capacity = newcap;
}

Map map_new() {
    Map map;
    map.size = 0;
    map.capacity = MAP_CAPACITY;
    map.entries = malloc(MAP_CAPACITY * sizeof(MapEntry));
    return map;
}

void* map_get(Map* map, String key) {
    for (size_t i = 0; i < map->size; i++) {
        MapEntry* pair = map->entries + i;
        if (pair->key == key) return pair->value;
    }
    return NULL;
}

void map_put(Map* map, String key, void* value) {
    for (size_t i = 0; i < map->size; i++) {
        MapEntry* entry = map->entries + i;
        if (entry->key == key) {
            entry->value = value;
            return;
        }
    }

    if (map->size == map->capacity) map_grow(map);

    MapEntry entry;
    entry.key = key;
    entry.value = value;
    map->entries[map->size++] = entry;
}