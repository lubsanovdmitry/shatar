//
// Created by dmitry on 09.03.23.
//

#ifndef SHATAR_POSITION_H
#define SHATAR_POSITION_H

#include "Board.h"
#include "Hash.h"
#include "Move.h"



class Position {
private:
    Board board;

    size_t move_ctr;
    Hash hash;
    size_t fifty_moves_ctr;
    RecentHistory recent_history;
public:
    Position(std::string_view sv, int move_ctr);

    void add_piece(size_t pos, size_t type, size_t color);

    void remove_piece(size_t pos, size_t type, size_t color);

    void update_ctr();

    void update_fifty_moves_ctr(bool reset);

    void apply_move(const Move &m);
};


#endif //SHATAR_POSITION_H
