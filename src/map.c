#include "../headers/map.h"

#include <stddef.h>
#include <malloc.h>

Map map_new() {
    Map map;
    map.first = NULL;
    map.last = NULL;
    return map;
}

MapEntry* map_find_entry(Map* map, String key) {
    MapEntry* entry = map->first;
    while (entry != NULL) {
        if (entry->key == key)
            return entry;
        entry = entry->next;
    }
    return NULL;
}

void* map_get(Map* map, String key) {
    MapEntry* entry = map_find_entry(map, key);
    if (entry != NULL)
        return entry->value;
    return NULL;
}

int map_contains_key(Map* map, String key) {
    MapEntry* entry = map->first;
    while (entry != NULL) {
        if (entry->key == key) return 1;
        entry = entry->next;
    }
    return 0;
}

MapEntry* map_entry_new(String key, void* value) {
    MapEntry* entry = malloc(sizeof(MapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

void map_put(Map* map, String key, void* value) {
    MapEntry* entry = map_find_entry(map, key);
    if (entry == NULL) {
        entry = map_entry_new(key, value);
        if (map->last == NULL) {
            map->first = entry;
            map->last = entry;
        } else {
            map->last->next = entry;
            map->last = entry;
        }
    } else {
        entry->value = value;
    }
}

void map_free(Map* map) {
    MapEntry* entry = map->first;
    while (entry != NULL) {
        MapEntry* next = entry->next;
        free(entry);
        entry = next;
    }
    map->first = NULL;
    map->last = NULL;
}