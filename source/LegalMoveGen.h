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
    static MoveList generate(Position position, bool side, bool only_captures = false);

private:
    static void _piece_mask_to_moves(Board b,
                                     Bitboard mask,
                                     uint8_t attacker_p,
                                     uint8_t attacker_type,
                                     bool attacker_side,
                                     MoveList &moves);

    static void _pawn_mask_to_moves(Board b,
                                    Bitboard mask,
                                    bool attacker_side,
                                    uint8_t attacker_index,
                                    bool look_for_defender,
                                    uint8_t flag,
                                    MoveList &moves);

    static bool _is_legal(Board b, Move move);
};


#endif //SHATAR_LEGALMOVEGEN_H
