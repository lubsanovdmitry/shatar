//
// Created by dmitry on 16.03.23.
//

#include "MoveList.h"

MoveList::MoveList() {
    this->_size = 0;
}
Move &MoveList::operator[](uint8_t index) {
    return this->_moves[index];
}
Move MoveList::operator[](uint8_t index) const {
    return this->_moves[index];
}
void MoveList::push_back(Move move) {
    this->_moves[this->_size] = move;
    this->_size++;
}
uint8_t MoveList::size() const {
    return this->_size;
}
