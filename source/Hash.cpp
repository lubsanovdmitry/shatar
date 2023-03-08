//
// Created by dmitry on 06.01.23.
//

#include "Hash.h"

Hash::Hash(const Board& b, bool color) noexcept {
    size_t _hash = 0;

    if (color) {
        _hash ^= __zobrist::black;
    }

    uint8_t side = 0;
    for (size_t bit = 0; bit < 64; ++bit) {
        if (b.look_side(Color::White).test(bit)) {
            side = Color::White;
        } else if(b.look_side(Color::Black).test(bit)){
            side = Color::Black;
        } else {
            continue;
        }

        for (size_t piece = 0; piece < 6; ++piece) {
            if (b.look_pieces(side, piece).test(bit)) {
                _hash = put_piece(bit, side, piece);
                break;
            }
        }
    }
    value = _hash;
}
