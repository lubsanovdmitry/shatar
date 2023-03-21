#include <iostream>
#include <string>

#include "Board.h"
#include "Hash.h"
#include "Players.h"
#include "Position.h"
#include "LegalMoveGen.h"

#include <rang.hpp>

int main(int argc, char *argv[]) {
    //std::cout << (1 << 2);
    std::string normal = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    std::string super = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R";
    std::string tst = "8/3p4/2P5/8/8/pppppPp1/8/8";
    //Position p("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R", 0);
    Position p(normal, 0);

    ///size_t from, size_t to, size_t type, size_t side, size_t eaten_type, size_t eaten_side, size_t flag
    p.apply_move(Move(to_pos("d7"), to_pos("d5"), Piece::Pawn, Color::Black,
                      Piece::None, Color::Black, Move::Flags::None));
    p.apply_move(Move(to_pos("d2"), to_pos("d4"), Piece::Pawn, Color::White,
                      Piece::None, Color::Black, Move::Flags::None));
    std::cout << p.board << std::endl;
    AI ai;
    Human h, h2;
    while (true) {
        MoveList ml = LegalMoveGen::generate(p, p.move_ctr % 2, 0);
        if (ml.size() == 0)
            break;

        Move m;
        if (p.move_ctr % 2 == 0) {
            m = h.getMove(p, p.move_ctr % 2, 0, 0);
        } else {
            m = ai.getMove(p, p.move_ctr % 2, 250, 5 * 1e+2);
        }
        if (m.type == Piece::None) {
            std::cout << "Invalid move\n";
            //p.update_ctr();
            //p.update_fifty_moves_ctr(0);
        }
        else {
            p.apply_move(m);
            std::cout << p.board << std::endl;
        }
    }
    return 0;
}
