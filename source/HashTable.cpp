//
// Created by dmitry on 20.03.23.
//

#include "HashTable.h"

void HashTable::add_entry(Hash h, Entry e) {
    auto hash_copy = this->mp.find(h.value);
    if (hash_copy == this->mp.end() or hash_copy->second.depth < e.depth)
        this->mp[h.value] = e;
}

size_t HashTable::find(Hash h) {
    auto entry = this->mp.find(h.value);
    if (entry == this->mp.end())
        return 255;
    return entry->second.best_move_index;
}
