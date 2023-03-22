//
// Created by dmitry on 15.03.23.
//

#include "PseudoLegalMoveMaskGen.h"

Bitboard PseudoLegalMoveMaskGen::generate_knight_mask(Board b, uint8_t p, bool side, bool only_captures) {
    Bitboard mv(0);
    /*std::cout << KnightMasks::Masks[p-24];
    if (only_captures) {
        return KnightMasks::Masks[p] & b.look_side(!side);
    }
    return KnightMasks::Masks[p] & (b._inverted_colors[side]);*/

    // -17 -10 +6 +15
    // -15 -6 +10 +17

    size_t p1 = p - 17, p2 = p - 10, p3 = p + 6, p4 = p + 15,
            p5 = p - 15, p6 = p - 6, p7 = p + 10, p8 = p + 17;
    if (p % 8 < 2)
        p2 = -1000, p3 = -1000;
    if (p % 8 > 5)
        p6 = -1000, p7 = -1000;
    if (p % 8 < 1)
        p1 = -1000, p4 = -1000;
    if (p % 8 > 6)
        p5 = -1000, p8 = -1000;
    if (p / 8 < 2)
        p1 = -1000, p5 = -1000;
    if (p / 8 < 1)
        p2 = -1000, p6 = -1000;
    if (p / 8 > 5)
        p4 = -1000, p8 = -1000;
    if (p / 8 > 6)
        p3 = -1000, p7 = -1000;
    if (!only_captures) {
        if (!b._colors[side].test(p1))
            mv.set(p1);
        if (!b._colors[side].test(p2))
            mv.set(p2);
        if (!b._colors[side].test(p3))
            mv.set(p3);
        if (!b._colors[side].test(p4))
            mv.set(p4);
        if (!b._colors[side].test(p5))
            mv.set(p5);
        if (!b._colors[side].test(p6))
            mv.set(p6);
        if (!b._colors[side].test(p7))
            mv.set(p7);
        if (!b._colors[side].test(p8))
            mv.set(p8);

    } else {
        if (b._colors[!side].test(p1))
            mv.set(p1);
        if (b._colors[!side].test(p2))
            mv.set(p2);
        if (b._colors[!side].test(p3))
            mv.set(p3);
        if (b._colors[!side].test(p4))
            mv.set(p4);
        if (b._colors[!side].test(p5))
            mv.set(p5);
        if (b._colors[!side].test(p6))
            mv.set(p6);
        if (b._colors[!side].test(p7))
            mv.set(p7);
        if (b._colors[!side].test(p8))
            mv.set(p8);
    }
    return mv;
}

Bitboard PseudoLegalMoveMaskGen::generate_king_mask(Board b, uint8_t p, bool side, bool only_captures) {
    if (only_captures) {
        return KingMasks::Masks[p] & b.look_side(!side);
    }
    return KingMasks::Masks[p] & b._inverted_colors[side];
}

Bitboard
PseudoLegalMoveMaskGen::calc_ray(Board b, size_t p, size_t side, bool only_captures, size_t direction, bool find_last) {
    Bitboard blockers = SlidersMasks::Masks[p][direction] & b._all_pieces;
    if (blockers.count() == 0) {
        if (only_captures)
            return {};
        return SlidersMasks::Masks[p][direction];
    }
    size_t blocking_square;

    if (find_last)
        blocking_square = blockers.find_last();
    else
        blocking_square = blockers.find_first();

    Bitboard moves;
    if (only_captures)
        moves = {};
    else
        moves = SlidersMasks::Masks[p][direction] ^ SlidersMasks::Masks[blocking_square][direction];

    if (b._colors[side].test(blocking_square))
        moves.reset(blocking_square);
    else
        moves.set(blocking_square);

    return moves;

}

Bitboard PseudoLegalMoveMaskGen::generate_bishop_mask(Board b, uint8_t p, bool side, bool only_captures) {
    Bitboard mv(0);
    //while (b._pieces[side][Piece::Bishop] != Bitboard(0)) {
    //size_t p = b._pieces[side][Piece::Bishop].find_last();
    size_t x = p % 8;
    size_t y = p / 8;
    if (!only_captures) {
        for (int s = 0; s < 8; ++s) {
            int i = x - 1 - s;
            int j = y - 1 - s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (!b._all_pieces.test(j * 8 + i)) {
                mv.set(j * 8 + i);
            } else {
                if (b._colors[!side].test(j * 8 + i))
                    mv.set(j * 8 + i);
                break;
            }

        }
        for (int s = 0; s < 8; ++s) {
            int i = x - 1 - s;
            int j = y + 1 + s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (!b._all_pieces.test(j * 8 + i)) {
                mv.set(j * 8 + i);
            } else {
                if (b._colors[!side].test(j * 8 + i))
                    mv.set(j * 8 + i);
                break;
            }
        }


        for (int s = 0; s < 8; ++s) {
            int i = x + 1 + s;
            int j = y - 1 - s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (!b._all_pieces.test(j * 8 + i)) {
                mv.set(j * 8 + i);
            } else {
                if (b._colors[!side].test(j * 8 + i))
                    mv.set(j * 8 + i);
                break;
            }
        }

        for (int s = 0; s < 8; ++s) {
            int i = x - 1 - s;
            int j = y - 1 - s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (!b._all_pieces.test(j * 8 + i)) {
                mv.set(j * 8 + i);
            } else {
                if (b._colors[!side].test(j * 8 + i))
                    mv.set(j * 8 + i);
                break;
            }
        }
    } else {
        for (int s = 0; s < 8; ++s) {
            int i = x - 1 - s;
            int j = y - 1 - s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (b._all_pieces.
                    test(j
                         * 8 + i)) {
                if (b._colors[!side].
                        test(j
                             * 8 + i))
                    mv.
                            set(j
                                * 8 + i);
                break;
            }
        }

        for (int s = 0; s < 8; ++s) {
            int i = x + 1 + s;
            int j = y - 1 - s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (b._all_pieces.
                    test(j
                         * 8 + i)) {
                if (b._colors[!side].
                        test(j
                             * 8 + i))
                    mv.
                            set(j
                                * 8 + i);
                break;
            }
        }

        for (int s = 0; s < 8; ++s) {
            int i = x - 1 - s;
            int j = y + 1 + s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (b._all_pieces.
                    test(j
                         * 8 + i)) {
                if (b._colors[!side].
                        test(j
                             * 8 + i))
                    mv.
                            set(j
                                * 8 + i);
                break;
            }
        }

        for (int s = 0; s < 8; ++s) {
            int i = x + 1 + s;
            int j = y + 1 + s;
            if (i < 0 || j < 0 || j > 7 || i > 7)
                break;
            if (b._all_pieces.
                    test(j
                         * 8 + i)) {
                if (b._colors[!side].
                        test(j
                             * 8 + i))
                    mv.set(j * 8 + i);
                break;
            }
        }
    }

    return mv;
}

Bitboard PseudoLegalMoveMaskGen::generate_rook_mask(Board b, uint8_t p, bool side, bool only_captures) {
    Bitboard mv(0);

    //size_t p = b._pieces[side][Piece::Rook].find_last();
    size_t x = p % 8;
    size_t y = p / 8;

    if (!only_captures) {
        for (int i = x - 1; i >= 0; --i) {
            if (!b._all_pieces.test(y * 8 + i)) {
                mv.set(y * 8 + i);
            } else {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            }
        }
        for (int i = x + 1; i < 8; ++i) {
            if (!b._all_pieces.test(y * 8 + x)) {
                mv.set(y * 8 + i);
            } else {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            }
        }

        for (int j = y - 1; j >= 0; --j) {
            if (!b._all_pieces.test(j * 8 + x)) {
                mv.set(j * 8 + x);
            } else {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            }
        }
        for (int j = y + 1; j < 8; ++j) {
            if (!b._all_pieces.test(j * 8 + x)) {
                mv.set(j * 8 + x);
            } else {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            }
        }
    } else {
        for (int i = x - 1; i >= 0; --i) {
            if (b._all_pieces.test(y * 8 + i)) {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            } else {

            }
        }
        for (int i = x + 1; i < 8; ++i) {
            if (b._all_pieces.test(y * 8 + x)) {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            } else {

            }
        }

        for (int j = y - 1; j >= 0; --j) {
            if (b._all_pieces.test(j * 8 + x)) {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            } else {

            }
        }
        for (int j = y + 1; j < 8; ++j) {
            if (b._all_pieces.test(j * 8 + x)) {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            } else {

            }
        }
    }

    return mv;
}

Bitboard PseudoLegalMoveMaskGen::generate_queen_mask(Board b, uint8_t p, bool side, bool only_captures) {
    Bitboard mv(0);

    //size_t p = b._pieces[side][Piece::Rook].find_last();
    size_t x = p % 8;
    size_t y = p / 8;

    if (!only_captures) {
        for (int i = x - 1; i >= 0; --i) {
            if (!b._all_pieces.test(y * 8 + i)) {
                mv.set(y * 8 + i);
            } else {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            }
        }
        for (int i = x + 1; i < 8; ++i) {
            if (!b._all_pieces.test(y * 8 + x)) {
                mv.set(y * 8 + i);
            } else {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            }
        }

        for (int j = y - 1; j >= 0; --j) {
            if (!b._all_pieces.test(j * 8 + x)) {
                mv.set(j * 8 + x);
            } else {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            }
        }
        for (int j = y + 1; j < 8; ++j) {
            if (!b._all_pieces.test(j * 8 + x)) {
                mv.set(j * 8 + x);
            } else {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            }
        }
        if (x > 0 && y > 0) {
            if (!b._colors[side].test((y - 1) * 8 + (x - 1))) {
                mv.set((y - 1) * 8 + (x - 1));
            }
        }
        if (x > 0 && y < 7) {
            if (!b._colors[side].test((y + 1) * 8 + (x - 1))) {
                mv.set((y + 1) * 8 + (x - 1));
            }
        }
        if (x < 7 && y > 0) {
            if (!b._colors[side].test((y - 1) * 8 + (x + 1))) {
                mv.set((y - 1) * 8 + (x + 1));
            }
        }
        if (x < 7 && y < 7) {
            if (!b._colors[side].test((y + 1) * 8 + (x + 1))) {
                mv.set((y + 1) * 8 + (x + 1));
            }
        }
    } else {
        for (int i = x - 1; i >= 0; --i) {
            if (b._all_pieces.test(y * 8 + i)) {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            }
        }
        for (int i = x + 1; i < 8; ++i) {
            if (b._all_pieces.test(y * 8 + x)) {
                if (b._colors[!side].test(y * 8 + i))
                    mv.set(y * 8 + i);
                break;
            }
        }

        for (int j = y - 1; j >= 0; --j) {
            if (b._all_pieces.test(j * 8 + x)) {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            }
        }
        for (int j = y + 1; j < 8; ++j) {
            if (b._all_pieces.test(j * 8 + x)) {
                if (b._colors[!side].test(j * 8 + x))
                    mv.set(j * 8 + x);
                break;
            }
        }
        if (x > 0 && y > 0) {
            if (b._colors[!side].test((y - 1) * 8 + (x - 1))) {
                mv.set((y - 1) * 8 + (x - 1));
            }
        }
        if (x > 0 && y < 7) {
            if (b._colors[!side].test((y + 1) * 8 + (x - 1))) {
                mv.set((y + 1) * 8 + (x - 1));
            }
        }
        if (x < 7 && y > 0) {
            if (b._colors[!side].test((y - 1) * 8 + (x + 1))) {
                mv.set((y - 1) * 8 + (x + 1));
            }
        }
        if (x < 7 && y < 7) {
            if (b._colors[!side].test((y + 1) * 8 + (x + 1))) {
                mv.set((y + 1) * 8 + (x + 1));
            }
        }
    }

    return mv;
}

Bitboard PseudoLegalMoveMaskGen::generate_pawn_mask(Board b, bool side) {
    if (side == Color::White) {
        auto p = b._pieces[Color::White][Piece::Pawn] >> 1;
        return (b._pieces[Color::White][Piece::Pawn] >> 1) & b._empty_spaces;
    }
    return (b._pieces[Color::Black][Piece::Pawn] << 1) & b._empty_spaces;
}

Bitboard PseudoLegalMoveMaskGen::generate_pawn_left_captures_mask(Board b, bool side, bool all) {
    if (side == Color::White) {
        Bitboard mask = (b._pieces[Color::White][Piece::Pawn] << 7) & BitboardColumns::InversionColumns[0]; //+7
        if (!all)
            mask = mask & b._colors[Color::Black];
        return mask;
    }

    Bitboard mask = (b._pieces[Color::Black][Piece::Pawn] << 9) & BitboardColumns::InversionColumns[7]; //+9
    if (!all)
        mask = mask & b._colors[Color::White];
    return mask;
}

Bitboard PseudoLegalMoveMaskGen::generate_pawn_right_captures_mask(Board b, bool side, bool all) {
    if (side == Color::White) {
        Bitboard mask = (b._pieces[Color::White][Piece::Pawn] >> 9) & BitboardColumns::InversionColumns[0]; //-9
        if (!all)
            mask = mask & b._colors[Color::Black];
        return mask;
    }

    Bitboard mask = (b._pieces[Color::Black][Piece::Pawn] >> 7) & BitboardColumns::InversionColumns[7]; //-7
    if (!all)
        mask = mask & b._colors[Color::White];
    return mask;
}

bool PseudoLegalMoveMaskGen::in_danger(Board b, uint8_t p, bool side) {

    Bitboard opposite_pawns_left_captures = generate_pawn_left_captures_mask(b, !side, true);
    Bitboard opposite_pawns_right_captures = generate_pawn_right_captures_mask(b, !side, true);
    Bitboard opposite_pawns_captures = opposite_pawns_left_captures | opposite_pawns_right_captures;

    if (opposite_pawns_captures.test(p))
        return true;

    if ((generate_knight_mask(b, p, side, true) & b._pieces[!side][Piece::Knight]).count())
        return true;
    if ((generate_bishop_mask(b, p, side, true) & b._pieces[!side][Piece::Bishop]).count())
        return true;
    if ((generate_queen_mask(b, p, side, true) & b._pieces[!side][Piece::Queen]).count())
        return true;
    if ((generate_king_mask(b, p, side, true) & b._pieces[!side][Piece::King]).count())
        return true;

    return false;

}
