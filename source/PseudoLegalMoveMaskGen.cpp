//
// Created by dmitry on 15.03.23.
//

#include "PseudoLegalMoveMaskGen.h"

Bitboard PseudoLegalMoveMaskGen::generate_knight_mask(Board b, size_t p, size_t side, bool only_captures) {
    if (only_captures) {
        return KnightMasks::Masks[p] & b.look_side(!side);
    }
    return KnightMasks::Masks[p] & (b._inverted_colors[side]);
}

Bitboard PseudoLegalMoveMaskGen::generate_king_mask(Board b, size_t p, size_t side, bool only_captures) {
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

Bitboard PseudoLegalMoveMaskGen::generate_bishop_mask(Board b, size_t p, size_t side, bool only_captures) {
    Bitboard nw = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::NorthWest, false);
    Bitboard ne = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::NorthEast, false);
    Bitboard sw = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::SouthWest, true);
    Bitboard se = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::SouthEast, true);

    return nw | ne | sw | se;
}

Bitboard PseudoLegalMoveMaskGen::generate_rook_mask(Board b, size_t p, size_t side, bool only_captures) {
    Bitboard n = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::North, false);
    Bitboard s = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::South, true);
    Bitboard w = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::West, true);
    Bitboard e = calc_ray(b, p, side, only_captures, SlidersMasks::Direction::East, false);

    return n | s | w | e;
}

Bitboard PseudoLegalMoveMaskGen::generate_queen_mask(Board b, size_t p, size_t side, bool only_captures) {
    Bitboard bishop_mask = generate_bishop_mask(b, p, side, only_captures);
    Bitboard rook_mask = generate_rook_mask(b, p, side, only_captures);

    return bishop_mask | rook_mask;
}

Bitboard PseudoLegalMoveMaskGen::generate_pawn_mask(Board b, size_t side) {
    if (side == Color::White) {
        auto p = b._pieces[Color::White][Piece::Pawn] >> 1;
        return (b._pieces[Color::White][Piece::Pawn] >> 1) & b._empty_spaces;
    }
    return (b._pieces[Color::Black][Piece::Pawn] << 1) & b._empty_spaces;
}

Bitboard PseudoLegalMoveMaskGen::generate_pawn_left_captures_mask(Board b, size_t side, bool all) {
    if (side == Color::White) {
        Bitboard mask = (b._pieces[Color::White][Piece::Pawn] << 7) & BitboardColumns::InversionColumns[7];
        if (!all)
            mask = mask & b._colors[Color::Black];
        return mask;
    }

    Bitboard mask = (b._pieces[Color::Black][Piece::Pawn] >> 9) & BitboardColumns::InversionColumns[7];
    if (!all)
        mask = mask & b._colors[Color::White];
    return mask;
}

Bitboard PseudoLegalMoveMaskGen::generate_pawn_right_captures_mask(Board b, size_t side, bool all) {
    if (side == Color::White) {
        Bitboard mask = (b._pieces[Color::White][Piece::Pawn] << 9) & BitboardColumns::InversionColumns[0];
        if (!all)
            mask = mask & b._colors[Color::Black];
        return mask;
    }

    Bitboard mask = (b._pieces[Color::Black][Piece::Pawn] >> 7) & BitboardColumns::InversionColumns[0];
    if (!all)
        mask = mask & b._colors[Color::White];
    return mask;
}

bool PseudoLegalMoveMaskGen::in_danger(Board b, size_t p, size_t side) {

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
