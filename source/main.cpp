#include <iostream>
#include <string>

#include "Board.h"
#include "Hash.h"
#include "Players.h"
#include "Position.h"
#include "LegalMoveGen.h"

#include <rang.hpp>

int main(int argc, char *argv[]) {
    std::string normal = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    std::string super = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R";
    std::string tst = "8/3p4/2P5/8/8/8/8/8";
    //Position p("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R", 0);
    Position p(tst, 0);
    std::cout << p.board << std::endl;
    MoveList ml = LegalMoveGen::generate(p, Color::White, 0);
    for (int i = 0; i < ml.size(); ++i) {
        auto pp = p;
        std::cout << MoveString::to_str(ml[i].from) << " to " << MoveString::to_str(ml[i].to) << std::endl;
        std::cout << ml[i].from << " to " << ml[i].to << std::endl;
        pp.apply_move(ml[i]);
        if (ml[i].type != 255)
        std::cout << pp.board << "\n-------------------\n";
    }
    return 0;
}
