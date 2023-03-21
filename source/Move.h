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
    Move() { from = 0, to = 0, type = Piece::None, side = 0, def_type = Piece::None, def_side = 0, flag = Flags::None; }

    //Move(uint8_t from, uint8_t to, uint8_t type, uint8_t side, uint8_t eaten_type, uint8_t eaten_side, uint8_t flag = Flags::None);
    Move(size_t from, size_t to, size_t type, size_t side, size_t eaten_type, size_t eaten_side,
         size_t flag = Flags::None);

    size_t from{}, to{}, type{}, side{}, def_type{}, def_side{}, flag{};

    enum Flags {
        None = 0,
        PromotedKnight = 7,
        PromotedBishop = 8,
        PromotedRook = 9,
        PromotedQueen = 10
    };

};


static constexpr size_t to_pos(std::string_view sv) {
    int y = toupper(sv[0]) - 'A';
    int x = -sv[1] + '8';
    return y * 8 + x;
}

static constexpr std::string to_str(size_t i) {
    std::string s = "  ";
    int y = i / 8;
    int x = i % 8;
    s[0] = y + 'A';
    s[1] = x + '1';
    return s;
}


#endif