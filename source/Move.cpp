//
// Created by dmitry on 09.03.23.
//

#include "Move.h"

/**
 * Move constructor
 *
 * @param from Field from
 * @param to Field to
 * @param type Type of attacker piece
 * @param side Color of attacker
 * @param eaten_type Type of defender piece
 * @param eaten_side Color of defender
 * @param flag Flags
 */

Move::Move(size_t from, size_t to, size_t type, size_t side, size_t eaten_type, size_t eaten_side, size_t flag) {
    this->from = from;
    this->to = to;
    this->side = side;
    this->type = type;
    this->def_side = eaten_side;
    this->def_type = eaten_type;
    this->flag = flag;
}
