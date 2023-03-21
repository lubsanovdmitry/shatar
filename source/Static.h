//
// Created by dmitry on 18.03.23.
//

#ifndef SHATAR_STATIC_H
#define SHATAR_STATIC_H


#include "Position.h"
#include "Board.h"
#include "LegalMoveGen.h"

struct Constant {
    static constexpr int Pawn = 100;
    static constexpr int Knight = 300;
    static constexpr int Bishop = 350;
    static constexpr int Rook = 500;
    static constexpr int Queen = 900;

    static constexpr int DoublePawn = -25;
    static constexpr int TwoBishops = 50;

    static constexpr int KingsProximity = 10;
    static constexpr int DistanceBwDefenderKingAndMiddle = 10;

    static constexpr int EngamePcs = 8;
};

struct Mobility {
    static constexpr int32_t Knight = 9;
    static constexpr int32_t Bishop = 4;
    static constexpr int32_t Rook = 3;
    static constexpr int32_t Queen = 3;
};

class Static {
public:

    static int evaluate(Board b);

private:
    static int material(Board b);

    static int double_pawns(Board b);

    static int mobility(Board b);

    static int endgame(Board b, bool white_leading);

    static int two_bishops(Board b);
};


#endif //SHATAR_STATIC_H
