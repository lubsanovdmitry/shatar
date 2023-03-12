//
//
// 

#ifndef MOVE_SHATAR_H
#define MOVE_SHATAR_H

#include <unordered_map>

#include "Board.h"
#include "Hash.h"



class RecentHistory {
private:
    std::unordered_map<size_t, size_t> hist;
public:
    void add(Hash h) { hist[h.value]++; }

    void clear() { hist.clear(); }

    size_t getRepetitionsCount(Hash h) { return hist[h.value]; }
};

class Move {
public:
    Move() = default;
    Move(uint8_t from, uint8_t to, uint8_t type, uint8_t side, uint8_t eaten_type, uint8_t eaten_side, uint8_t flag = Flags::None);

    uint8_t from, to, type, side, def_type, def_side, flag;

    enum Flags {
        None = 0,
        PromotedKnight = 7,
        PromotedBishop = 8,
        PromotedRook = 9,
        PromotedQueen = 10
    };

};

#endif