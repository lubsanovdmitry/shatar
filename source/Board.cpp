//
// Created by dmitry on 05.01.23.
//

#include <iostream>
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
                ++row;
                break;
            case 'n':
                _pieces[Color::Black][Piece::Knight].set(bit);
                ++row;
                break;
            case 'b':
                _pieces[Color::Black][Piece::Bishop].set(bit);
                ++row;
                break;
            case 'q':
                _pieces[Color::Black][Piece::Queen].set(bit);
                ++row;
                break;
            case 'k':
                _pieces[Color::Black][Piece::King].set(bit);
                ++row;
                break;
            case 'p':
                _pieces[Color::Black][Piece::Pawn].set(bit);
                ++row;
                break;
            case 'R':
                _pieces[Color::White][Piece::Rook].set(bit);
                ++row;
                break;
            case 'N':
                _pieces[Color::White][Piece::Knight].set(bit);
                ++row;
                break;
            case 'B':
                _pieces[Color::White][Piece::Bishop].set(bit);
                ++row;
                break;
            case 'Q':
                _pieces[Color::White][Piece::Queen].set(bit);
                ++row;
                break;
            case 'K':
                _pieces[Color::White][Piece::King].set(bit);
                ++row;
                break;
            case 'P':
                _pieces[Color::White][Piece::Pawn].set(bit);
                ++row;
                break;
            case '/':
                row = 0;
                ++col;
                break;
            default:
                row += (c - '0');
                break;
        }
        //std::cerr << *this << std::endl;
    }
    update();
}

std::ostream &operator<<(std::ostream &os, const Board &b) {
    os << "  ABCDEFGH\n";
    for (size_t x = 0; x < 8; ++x) {
        os << (char)('8' - x) << ' ';
        for (size_t y = 0; y < 8; ++y) {
            size_t bit = y * 8 + x;
            if (b.look_pieces(Color::White, Piece::Pawn).test(bit)) os << 'P';
            else if (b.look_pieces(Color::White, Piece::Rook).test(bit)) os << 'R';
            else if (b.look_pieces(Color::White, Piece::Knight).test(bit)) os << 'N';
            else if (b.look_pieces(Color::White, Piece::Bishop).test(bit)) os << 'B';
            else if (b.look_pieces(Color::White, Piece::Queen).test(bit)) os << 'Q';
            else if (b.look_pieces(Color::White, Piece::King).test(bit)) os << 'K';
            else if (b.look_pieces(Color::Black, Piece::Pawn).test(bit)) os << 'p';
            else if (b.look_pieces(Color::Black, Piece::Rook).test(bit)) os << 'r';
            else if (b.look_pieces(Color::Black, Piece::Knight).test(bit)) os << 'n';
            else if (b.look_pieces(Color::Black, Piece::Bishop).test(bit)) os << 'b';
            else if (b.look_pieces(Color::Black, Piece::Queen).test(bit)) os << 'q';
            else if (b.look_pieces(Color::Black, Piece::King).test(bit)) os << 'k';
            else os << ' ';
            //if ((bit + 1) % 8 == 0)
               // os << std::endl;
        }
        os << std::endl;
    }
    return os;
}
