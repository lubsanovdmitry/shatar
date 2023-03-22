//
// Created by dmitry on 18.03.23.
//

#include "Static.h"

int Static::material(Board b) {
    int res = 0;
    res += Constant::Pawn *
           (int) (b._pieces[Color::White][Piece::Pawn].count() - b._pieces[Color::Black][Piece::Pawn].count());
    res += Constant::Knight *
           (int) (b._pieces[Color::White][Piece::Knight].count() - b._pieces[Color::Black][Piece::Knight].count());
    res += Constant::Rook *
           (int) (b._pieces[Color::White][Piece::Rook].count() - b._pieces[Color::Black][Piece::Rook].count());
    res += Constant::Bishop *
           (int) (b._pieces[Color::White][Piece::Bishop].count() - b._pieces[Color::Black][Piece::Bishop].count());
    res += Constant::Queen *
           (int) (b._pieces[Color::White][Piece::Queen].count() - b._pieces[Color::Black][Piece::Queen].count());
    res += 25 - (rand() % 50);
    return res;
}

int Static::double_pawns(Board b) {


    int double_pawn_ctr = 0;

    int white_pawns;
    int black_pawns;

    for (uint8_t x = 0; x < 8; x = x + 1) {
        white_pawns = (b._pieces[Color::White][Piece::Pawn] & BitboardColumns::Columns[x]).count();
        black_pawns = (b._pieces[Color::Black][Piece::Pawn] & BitboardColumns::Columns[x]).count();

        double_pawn_ctr += std::max(0, white_pawns - 1);
        double_pawn_ctr -= std::max(0, black_pawns - 1);
    }

    int double_pawn = Constant::DoublePawn * double_pawn_ctr;

    return double_pawn;
}

int Static::mobility(Board b) {
    int mobility = 0;

    std::array<std::array<Bitboard, 6>, 2> iteration_masks = b._pieces;
    size_t index;

    int knight_moves = 0;
    int bishop_moves = 0;
    int rook_moves = 0;
    int queen_moves = 0;

    while (iteration_masks[Color::White][Piece::Knight] != Bitboard(0)) {
        index = iteration_masks[Color::White][Piece::Knight].find_last();
        iteration_masks[Color::White][Piece::Knight].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_knight_mask(b, index, Color::White, false).count();
    }
    while (iteration_masks[Color::White][Piece::Bishop] != Bitboard(0)) {
        index = iteration_masks[Color::White][Piece::Bishop].find_last();
        iteration_masks[Color::White][Piece::Bishop].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_bishop_mask(b, index, Color::White, false).count();
    }
    while (iteration_masks[Color::White][Piece::Rook] != Bitboard(0)) {
        index = iteration_masks[Color::White][Piece::Rook].find_last();
        iteration_masks[Color::White][Piece::Rook].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_rook_mask(b, index, Color::White, false).count();
    }
    while (iteration_masks[Color::White][Piece::Queen] != Bitboard(0)) {
        index = iteration_masks[Color::White][Piece::Queen].find_last();
        iteration_masks[Color::White][Piece::Queen].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_queen_mask(b, index, Color::White, false).count();
    }

    while (iteration_masks[Color::Black][Piece::Knight] != Bitboard(0)) {
        index = iteration_masks[Color::Black][Piece::Knight].find_last();
        iteration_masks[Color::Black][Piece::Knight].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_knight_mask(b, index, Color::Black, false).count();
    }
    while (iteration_masks[Color::Black][Piece::Bishop] != Bitboard(0)) {
        index = iteration_masks[Color::Black][Piece::Bishop].find_last();
        iteration_masks[Color::Black][Piece::Bishop].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_bishop_mask(b, index, Color::Black, false).count();
    }
    while (iteration_masks[Color::Black][Piece::Rook] != Bitboard(0)) {
        index = iteration_masks[Color::Black][Piece::Rook].find_last();
        iteration_masks[Color::Black][Piece::Rook].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_rook_mask(b, index, Color::Black, false).count();
    }
    while (iteration_masks[Color::Black][Piece::Queen] != Bitboard(0)) {
        index = iteration_masks[Color::Black][Piece::Queen].find_last();
        iteration_masks[Color::Black][Piece::Queen].reset(index);
        knight_moves += PseudoLegalMoveMaskGen::generate_queen_mask(b, index, Color::Black, false).count();
    }

    mobility += Mobility::Knight * knight_moves;
    mobility += Mobility::Bishop * bishop_moves;
    mobility += Mobility::Rook * rook_moves;
    mobility += Mobility::Queen * queen_moves;

    return mobility;
}

int Static::endgame(Board b, bool white_leading) {
    int endgame = 0;

    if (b._all_pieces.count() > Constant::EngamePcs)
        return 0;

    size_t attacker_side;
    size_t defender_side;

    if (white_leading) {
        attacker_side = Color::White;
        defender_side = Color::Black;
    } else {
        attacker_side = Color::Black;
        defender_side = Color::White;
    }

    uint8_t attacker_king_p = b._pieces[attacker_side][Piece::King].find_last();
    uint8_t attacker_king_x = attacker_king_p % 8;
    uint8_t attacker_king_y = attacker_king_p / 8;

    uint8_t defender_king_p = b._pieces[defender_side][Piece::King].find_last();
    uint8_t defender_king_x = defender_king_p % 8;
    uint8_t defender_king_y = defender_king_p / 8;

    endgame += Constant::KingsProximity *
               (16 - std::abs(attacker_king_x - defender_king_x) - std::abs(attacker_king_y - defender_king_y));
    endgame +=
            Constant::DistanceBwDefenderKingAndMiddle * (std::abs(defender_king_x - 3) + std::abs(defender_king_y - 4));

    if (!white_leading)
        endgame = -endgame;

    return endgame;
}

int Static::two_bishops(Board b) {
    int two_bishops = 0;

    if (b._pieces[Color::White][Piece::Bishop].count() >= 2) two_bishops = two_bishops + Constant::TwoBishops;
    if (b._pieces[Color::Black][Piece::Bishop].count() >= 2) two_bishops = two_bishops - Constant::TwoBishops;

    return two_bishops;
}

int Static::evaluate(Board b) {
    return  material(b) +
            double_pawns(b) +
            mobility(b) +
            two_bishops(b) +
            endgame(b, material(b) >= 0);
}
