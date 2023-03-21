//
// Created by dmitry on 16.03.23.
//

#ifndef SHATAR_MOVELIST_H
#define SHATAR_MOVELIST_H

#include <array>

#include "Move.h"
#include "Board.h"



class MoveList {
public:
    MoveList();

    Move &operator[](uint8_t index);
    Move operator[](uint8_t index) const;

    void push_back(Move move);
    [[nodiscard]] uint8_t size() const;

    std::array<Move, 218> _moves{Move()};
    uint8_t _size;
};


#endif //SHATAR_MOVELIST_H
