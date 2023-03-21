//
// Created by dmitry on 20.03.23.
//

#ifndef SHATAR_MOVESORT_H
#define SHATAR_MOVESORT_H

#include "MoveList.h"
#include "Board.h"
#include "LegalMoveGen.h"
#include "Static.h"


class MoveSort {
public:
    static MoveList sort(Board b, MoveList ml);
private:
    static int move_eval(Board b, Move m);
};


#endif //SHATAR_MOVESORT_H
