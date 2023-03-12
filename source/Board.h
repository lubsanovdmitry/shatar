//
// Created by dmitry on 05.01.23.
//

#ifndef SHATAR_BOARD_H
#define SHATAR_BOARD_H

#include <array>
#include <string_view>
#include <ostream>

#include "Bitboard.h"

struct Piece {
    static constexpr size_t Pawn = 0;
    static constexpr size_t Knight = 1;
    static constexpr size_t Bishop = 2;
    static constexpr size_t Rook = 3;
    static constexpr size_t Queen = 4;
    static constexpr size_t King = 5;
};

struct Color {
    static constexpr size_t White = 0;
    static constexpr size_t Black = 1;
};

class Board {
    //pawn king queen knight rook bishop
    std::array<std::array<Bitboard, 6>, 2> _pieces;
    std::array<Bitboard, 2> _colors;
    std::array<Bitboard, 2> _inverted_colors;
    Bitboard _all_pieces, _empty_spaces;

public:

    Board() = default;

    Board(std::string_view sv);

    constexpr bool operator==(const Board &other) const {
        return _pieces == other._pieces;
    }

    void update();

    const Bitboard &look_pieces(size_t color, size_t piece) const {
        return _pieces[color][piece];
    }

    const Bitboard &look_side(size_t color) const {
        return _colors[color];
    }

    Bitboard &get_pieces(size_t color, size_t piece) {
        return _pieces[color][piece];
    }

    Bitboard &get_side(size_t color){
        return _colors[color];
    }

    friend std::ostream& operator<< (std::ostream& os, const Board &b);
};

#endif //SHATAR_BOARD_H
