//
// Created by dmitry on 20.03.23.
//

#ifndef SHATAR_HASHTABLE_H
#define SHATAR_HASHTABLE_H

#include <unordered_map>

#include "Hash.h"

struct Entry {
    int depth;
    size_t best_move_index;
};

class HashTable {
public:
    HashTable() = default;

    void add_entry(Hash h, Entry e);

    size_t find(Hash h);

private:
    std::unordered_map<size_t, Entry> mp;
};


#endif //SHATAR_HASHTABLE_H
