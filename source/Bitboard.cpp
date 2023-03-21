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

std::ostream &operator<<(std::ostream &os, Bitboard b) {
    for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
            if (b.test(y * 8 + x)) {
                os << rang::bg::red << std::setw(2) <<y*8+x << rang::bg::reset << ' ';
            } else {
                os << std::setw(2) << y*8+x << ' ';
            }
        }
        os << std::endl;
    }
    os << std::endl;
    return os;
}
