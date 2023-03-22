//
// Created by dmitry on 09.03.23.
//

#ifndef SHATAR_POSITION_H
#define SHATAR_POSITION_H

#include "Board.h"
#include "Hash.h"
#include "Move.h"



class Position {
public:

    Position() = default;

    Board board;

    uint16_t move_ctr;
    Hash hash;
    uint16_t fifty_moves_ctr;
    RecentHistory recent_history;

    Position(std::string_view sv, uint16_t move_ctr);

    void add_piece(uint8_t pos, uint8_t type, bool color);

    void remove_piece(uint8_t pos, uint8_t type, bool color);

    void update_ctr();

    void update_fifty_moves_ctr(bool reset);

    void apply_move(const Move &m);
};


#endif //SHATAR_POSITION_H
