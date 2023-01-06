//
// Created by dmitry on 05.01.23.
//

#include "Board.h"

void Board::update() {
    _colors[Color::White] = _pieces[Color::White][Piece::Pawn] |
                            _pieces[Color::White][Piece::Knight] |
                            _pieces[Color::White][Piece::Bishop] |
                            _pieces[Color::White][Piece::Rook] |
                            _pieces[Color::White][Piece::Queen] |
                            _pieces[Color::White][Piece::King];
    _colors[Color::Black] = _pieces[Color::Black][Piece::Pawn] |
                            _pieces[Color::Black][Piece::Knight] |
                            _pieces[Color::Black][Piece::Bishop] |
                            _pieces[Color::Black][Piece::Rook] |
                            _pieces[Color::Black][Piece::Queen] |
                            _pieces[Color::Black][Piece::King];
    _inverted_colors[Color::White] = ~_colors[Color::White];
    _inverted_colors[Color::Black] = ~_colors[Color::Black];
    _all_pieces = _colors[Color::White] | _colors[Color::Black];
    _empty_spaces = ~_all_pieces;
}

Board::Board(std::string_view sv) {
    size_t row = 0;
    size_t col = 0;
    for (char c : sv) {
        size_t bit = row*8 + col;
        switch (c) {
            case 'r':
                _pieces[Color::Black][Piece::Rook].set(bit);
                ++col;
                break;
            case 'n':
                _pieces[Color::Black][Piece::Knight].set(bit);
                ++col;
                break;
            case 'b':
                _pieces[Color::Black][Piece::Bishop].set(bit);
                ++col;
                break;
            case 'q':
                _pieces[Color::Black][Piece::Queen].set(bit);
                ++col;
                break;
            case 'k':
                _pieces[Color::Black][Piece::King].set(bit);
                ++col;
                break;
            case 'p':
                _pieces[Color::Black][Piece::Pawn].set(bit);
                ++col;
                break;
            case 'R':
                _pieces[Color::White][Piece::Rook].set(bit);
                ++col;
                break;
            case 'N':
                _pieces[Color::White][Piece::Knight].set(bit);
                ++col;
                break;
            case 'B':
                _pieces[Color::White][Piece::Bishop].set(bit);
                ++col;
                break;
            case 'Q':
                _pieces[Color::White][Piece::Queen].set(bit);
                ++col;
                break;
            case 'K':
                _pieces[Color::White][Piece::King].set(bit);
                ++col;
                break;
            case 'P':
                _pieces[Color::White][Piece::Pawn].set(bit);
                ++col;
                break;
            case '/':
                col = 0;
                ++row;
                break;
            default:
                col += (c - '0');
                break;
        }
    }
    update();
}
