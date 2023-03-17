//
// Created by dmitry on 16.03.23.
//

#ifndef SHATAR_LEGALMOVEGEN_H
#define SHATAR_LEGALMOVEGEN_H

#include "MoveList.h"
#include "Move.h"
#include "Board.h"
#include "Position.h"
#include "PseudoLegalMoveMaskGen.h"


class LegalMoveGen {
public:
    static MoveList generate(Position position, size_t side, bool only_captures = false);

private:
    static void _piece_mask_to_moves(Board b,
                                     Bitboard mask,
                                     size_t attacker_p,
                                     size_t attacker_type,
                                     size_t attacker_side,
                                     MoveList &moves);

    static void _pawn_mask_to_moves(Board b,
                                    Bitboard mask,
                                    size_t attacker_side,
                                    int8_t attacker_index,
                                    bool look_for_defender,
                                    size_t flag,
                                    MoveList &moves);

    static bool _is_legal(Board b, Move move);
};


#endif //SHATAR_LEGALMOVEGEN_H
