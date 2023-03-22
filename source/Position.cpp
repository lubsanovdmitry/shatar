//
// Created by dmitry on 09.03.23.
//

#include "Position.h"

Position::Position(std::string_view sv, uint16_t move_ctr) {
    this->board = Board(sv);
    this->move_ctr = move_ctr;
    this->hash = Hash(board, move_ctr % 2);
    this->recent_history.add(this->hash);
    this->fifty_moves_ctr = 0;
}

void Position::add_piece(uint8_t pos, uint8_t type, bool color) {
    if (!this->board._pieces[color][type].test(pos)) {
        this->board._pieces[color][type].set(pos);
        this->hash.put_piece(pos, color, type);
    }
}

void Position::remove_piece(uint8_t pos, uint8_t type, bool color) {
    if (this->board._pieces[color][type].test(pos)) {
        this->board._pieces[color][type].reset(pos);
        this->hash.put_piece(pos, color, type);
    }
}

void Position::update_ctr() {
    this->move_ctr++;
    this->hash.invert();
}

void Position::update_fifty_moves_ctr(bool reset) {
    if (reset)
        this->fifty_moves_ctr = 0;
    else
        this->fifty_moves_ctr++;
}

void Position::apply_move(const Move &m) {
    this->remove_piece(m.from, m.type, m.side);
    this->add_piece(m.to, m.type, m.side);
    if (m.def_type != Piece::None)
        this->remove_piece(m.to, m.def_type, m.def_side);

    switch (m.flag) {
        case Move::Flags::PromotedBishop:
            this->remove_piece(m.to, Piece::Pawn, m.side);
            this->add_piece(m.to, Piece::Bishop, m.side);
            break;
        case Move::Flags::PromotedKnight:
            this->remove_piece(m.to, Piece::Pawn, m.side);
            this->add_piece(m.to, Piece::Knight, m.side);
            break;
        case Move::Flags::PromotedQueen:
            this->remove_piece(m.to, Piece::Pawn, m.side);
            this->add_piece(m.to, Piece::Queen, m.side);
            break;
        case Move::Flags::PromotedRook:
            this->remove_piece(m.to, Piece::Pawn, m.side);
            this->add_piece(m.to, Piece::Rook, m.side);
            break;
    }
    this->board.update();
    this->update_ctr();
    this->update_fifty_moves_ctr(m.type == Piece::Pawn || m.def_type != 0xFF);
    if (m.type == Piece::Pawn || m.def_type != 0xFF)
        this->recent_history.clear();
    this->recent_history.add(this->hash);
}
