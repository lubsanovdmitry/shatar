//
// Created by dmitry on 15.03.23.
//

#ifndef SHATAR_PSEUDOLEGALMOVEMASKGEN_H
#define SHATAR_PSEUDOLEGALMOVEMASKGEN_H

#include "Bitboard.h"
#include "Board.h"
#include "MoveMasks.h"


class PseudoLegalMoveMaskGen {
public:
    static Bitboard generate_knight_mask(Board b, uint8_t p, bool side, bool only_captures);
    static Bitboard generate_bishop_mask(Board b, uint8_t p, bool side, bool only_captures);
    static Bitboard generate_rook_mask(Board b, uint8_t p, bool side, bool only_captures);
    static Bitboard generate_queen_mask(Board b, uint8_t p, bool side, bool only_captures);
    static Bitboard generate_king_mask(Board b, uint8_t p, bool side, bool only_captures);

    static Bitboard generate_pawn_mask(Board b, bool side);
    static Bitboard generate_pawn_left_captures_mask(Board b, bool side, bool all);
    static Bitboard generate_pawn_right_captures_mask(Board b, bool side, bool all);

    static bool in_danger(Board b, uint8_t p, bool side);
private:
    static Bitboard calc_ray(Board b, size_t p, size_t side, bool only_captures, size_t direction, bool find_first);
};


#endif //SHATAR_PSEUDOLEGALMOVEMASKGEN_H
