//
// Created by dmitry on 02.01.23.
//

#include "Bitboard.h"

size_t Bitboard::find_first() {
    size_t b = _b.to_ullong();
    b |= b >> 1;
    b |= b >> 2;
    b |= b >> 4;
    b |= b >> 8;
    b |= b >> 16;
    b |= b >> 32;
    return _BST[(b * MAGIC) >> 58];
}
