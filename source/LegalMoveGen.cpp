//
// Created by dmitry on 16.03.23.
//

#include "LegalMoveGen.h"

MoveList LegalMoveGen::generate(Position position, bool side, bool only_captures) {
    MoveList moves;

    Bitboard pawn_left_captures_mask = PseudoLegalMoveMaskGen::generate_pawn_left_captures_mask(position.board, side, false);
    Bitboard pawn_right_captures_mask = PseudoLegalMoveMaskGen::generate_pawn_right_captures_mask(position.board, side, false);

    int8_t pawn_left_capture;
    int8_t pawn_right_capture;

    if (side == Color::White) {
        pawn_left_capture = -7;
        pawn_right_capture = -9;
    }
    else {
        pawn_left_capture = 9;
        pawn_right_capture = 7;
    }

    LegalMoveGen::_pawn_mask_to_moves(position.board, pawn_left_captures_mask, side, pawn_left_capture, true,Move::Flags::None, moves);
    LegalMoveGen::_pawn_mask_to_moves(position.board, pawn_right_captures_mask, side, pawn_right_capture, true,Move::Flags::None, moves);

    if (!only_captures) {
        Bitboard pawn_default_mask = PseudoLegalMoveMaskGen::generate_pawn_mask(position.board, side);

        int8_t pawn_default_move;

        if (side == Color::White) {
            pawn_default_move = +1;
        }
        else {
            pawn_default_move = -1;
        }

        LegalMoveGen::_pawn_mask_to_moves(position.board, pawn_default_mask, side, pawn_default_move, false,Move::Flags::None, moves);
        //LegalMoveGen::_pawn_mask_to_moves(position.board, pawn_long_mask, side, pawn_long_move, false,Move::Flag::PawnLongMove, moves);
    }

    Bitboard all_knights = position.board._pieces[side][Piece::Knight];
    Bitboard all_bishops = position.board._pieces[side][Piece::Bishop];
    Bitboard all_rooks = position.board._pieces[side][Piece::Rook];
    Bitboard all_queens = position.board._pieces[side][Piece::Queen];
    Bitboard all_kings = position.board._pieces[side][Piece::King];
    uint8_t attacker_p;
    Bitboard mask;

    while (all_knights != Bitboard(0)) {
        attacker_p = all_knights.find_last();
        all_knights.reset(attacker_p);
        mask = PseudoLegalMoveMaskGen::generate_knight_mask(position.board, attacker_p, side, only_captures);
        LegalMoveGen::_piece_mask_to_moves(position.board, mask, attacker_p, Piece::Knight, side, moves);
    }
    while (all_bishops != Bitboard(0)) {
        attacker_p = all_bishops.find_last();
        all_bishops.reset(attacker_p);
        mask = PseudoLegalMoveMaskGen::generate_bishop_mask(position.board, attacker_p, side, only_captures);
        //std::cout << mask;
        LegalMoveGen::_piece_mask_to_moves(position.board, mask, attacker_p, Piece::Bishop, side, moves);
    }
    while (all_rooks != Bitboard(0)) {
        attacker_p = all_rooks.find_last();
        all_rooks.reset(attacker_p);
        mask = PseudoLegalMoveMaskGen::generate_rook_mask(position.board, attacker_p, side, only_captures);
        //std::cout << mask;
        LegalMoveGen::_piece_mask_to_moves(position.board, mask, attacker_p, Piece::Rook, side, moves);
    }
    while (all_queens != Bitboard(0)) {
        attacker_p = all_queens.find_last();
        all_queens.reset(attacker_p);
        mask = PseudoLegalMoveMaskGen::generate_queen_mask(position.board, attacker_p, side, only_captures);
        LegalMoveGen::_piece_mask_to_moves(position.board, mask, attacker_p, Piece::Queen, side, moves);
    }

    /**/
    if (true) {
        while (all_kings != Bitboard(0)) {
            attacker_p = all_kings.find_last();
            all_kings.reset(attacker_p);
            mask = PseudoLegalMoveMaskGen::generate_king_mask(position.board, attacker_p, side, only_captures);
            LegalMoveGen::_piece_mask_to_moves(position.board, mask, attacker_p, Piece::King, side, moves);
        }
    }

    return moves;
}

void LegalMoveGen::_piece_mask_to_moves(Board b, Bitboard mask, uint8_t attacker_p, uint8_t attacker_type,
                                        bool attacker_side, MoveList &moves) {
    uint8_t defender_p;
    uint8_t defender_type;

    Move move{};

    while (mask != Bitboard(0)) {
        defender_p = mask.find_last();
        mask.reset(defender_p);

        defender_type = 255;
        for (uint8_t i = 0; i < 6; i = i + 1) {
            if (b._pieces[!attacker_side][i].test(defender_p)) {
                defender_type = i;
                break;
            }
        }

        move = {attacker_p, defender_p, attacker_type, attacker_side, defender_type, !attacker_side};

        if (LegalMoveGen::_is_legal(b, move))
            moves.push_back(move);
    }
}

void LegalMoveGen::_pawn_mask_to_moves(Board b, Bitboard mask, bool attacker_side, uint8_t attacker_index,
                                       bool look_for_defender, uint8_t flag, MoveList &moves) {
    uint8_t defender_p;
    uint8_t defender_type = 255;

    Move move{};

    while (mask != Bitboard(0)) {
        defender_p = mask.find_first();
        mask.reset(defender_p);

        if (look_for_defender) {
            defender_type = 255;
            for (uint8_t i = 0; i < 6; i = i + 1) {
                if (b._pieces[!attacker_side][i].test(defender_p)) {
                    defender_type = i;
                    break;
                }
            }
        }

        move = {(uint8_t)(defender_p + attacker_index), (uint8_t )defender_p, Piece::Pawn, attacker_side, defender_type, !attacker_side, flag};

        if (LegalMoveGen::_is_legal(b, move)) {
            if (defender_p % 8 == 0 || defender_p % 8 == 7) {
                moves.push_back({(uint8_t)(defender_p + attacker_index), (uint8_t)defender_p, 0, attacker_side, defender_type, !attacker_side, Move::Flags::PromotedKnight});
                moves.push_back({(uint8_t)(defender_p + attacker_index), (uint8_t)defender_p, 0, attacker_side, defender_type, !attacker_side, Move::Flags::PromotedBishop});
                moves.push_back({(uint8_t)(defender_p + attacker_index), (uint8_t)defender_p, 0, attacker_side, defender_type, !attacker_side, Move::Flags::PromotedRook});
                moves.push_back({(uint8_t)(defender_p + attacker_index), (uint8_t)defender_p, 0, attacker_side, defender_type, !attacker_side, Move::Flags::PromotedQueen});
            }
            else
                moves.push_back(move);
        }
    }
}

bool LegalMoveGen::_is_legal(Board b, Move move) {
    if (b._colors[move.side].test(move.to))
        return false;
    b._pieces[move.side][move.type].reset(move.from);
    b._pieces[move.side][move.type].set(move.to);
    if (move.def_type != 255)
        b._pieces[move.def_side][move.def_type].reset(move.to);
    /*if (en_passant_capture) {
        if (move.side == Color::White)
            b._pieces[Color::Black][Piece::Pawn].reset(move.to - 8);
        b._pieces[Color::White][Piece::Pawn].reset(move.to + 8);
    }*/

    b.update();

    if (PseudoLegalMoveMaskGen::in_danger(b, b._pieces[move.side][Piece::King].find_last(), move.side))
        return false;

    return true;
}
