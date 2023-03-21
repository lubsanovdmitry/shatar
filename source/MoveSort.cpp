//
// Created by dmitry on 20.03.23.
//

#include "MoveSort.h"

int MoveSort::move_eval(Board b, Move m) {
    int32_t evaluation = 0;

    if (m.type != Piece::Pawn) {
        Bitboard opponent_pawn_attacks = PseudoLegalMoveMaskGen::generate_pawn_left_captures_mask(b, !m.side, true) |
                                         PseudoLegalMoveMaskGen::generate_pawn_right_captures_mask(b, !m.side, true);
        if (opponent_pawn_attacks.test(m.to)) {
            switch (m.type) {
                case Piece::Knight:
                    evaluation = evaluation - Constant::Knight;
                    break;
                case Piece::Bishop:
                    evaluation = evaluation - Constant::Bishop;
                    break;
                case Piece::Rook:
                    evaluation = evaluation - Constant::Rook;
                    break;
                case Piece::Queen:
                    evaluation = evaluation - Constant::Queen;
                    break;
            }
        }
    }

    if (m.def_type != Piece::None) {
        switch (m.def_type) {
            case Piece::Pawn:
                evaluation = evaluation + 1000 * Constant::Pawn;
                break;
            case Piece::Knight:
                evaluation = evaluation + 1000 * Constant::Knight;
                break;
            case Piece::Bishop:
                evaluation = evaluation + 1000 * Constant::Bishop;
                break;
            case Piece::Rook:
                evaluation = evaluation + 1000 * Constant::Rook;
                break;
            case Piece::Queen:
                evaluation = evaluation + 1000 * Constant::Queen;
                break;
        }
        switch (m.type) {
            case Piece::Pawn:
                evaluation = evaluation - Constant::Pawn;
                break;
            case Piece::Knight:
                evaluation = evaluation - Constant::Knight;
                break;
            case Piece::Bishop:
                evaluation = evaluation - Constant::Bishop;
                break;
            case Piece::Rook:
                evaluation = evaluation - Constant::Rook;
                break;
            case Piece::Queen:
                evaluation = evaluation - Constant::Queen;
                break;
        }
    }

    return evaluation;
}

MoveList MoveSort::sort(Board b, MoveList ml) {
    /*for (uint8_t i = 0; i < moves.size() - 1; i = i + 1) {
        for (uint8_t j = 0; j < moves.size() - i - 1; j = j + 1) {
            if (MoveSorter::_evaluate_move(pieces, moves[j]) < MoveSorter::_evaluate_move(pieces, moves[j + 1])) std::swap(moves[j], moves[j + 1]);
        }
    }

    return moves;*/
    std::sort(ml._moves.begin(), ml._moves.end(), [b](Move &lhs, Move &rhs)->bool{
        return move_eval(b, lhs) > move_eval(b, rhs);
    });
}
