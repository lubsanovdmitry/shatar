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
