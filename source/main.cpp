#include <iostream>
#include <string>
#include <ctime>

#include "Board.h"
#include "Hash.h"
#include "Players.h"
#include "Position.h"
#include "LegalMoveGen.h"

#include <rang.hpp>

int main(int argc, char *argv[]) {
    srand(time(nullptr));
    //std::cout << (1 << 2);
    std::string normal = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    std::string super = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R";
    //std::string tst = "8/3p4/2P5/8/8/pPp1pPp1/8/8";
    std::string tt = "2b5/3n4/p1k3Q1/R1p5/7R/1P2P3/2PPNPP1/4K3";
    //Position p("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R", 0);
    Position p(normal, 0);

    ///size_t from, size_t to, size_t type, size_t side, size_t eaten_type, size_t eaten_side, size_t flag
    /*p.apply_move(Move(to_pos("d7"), to_pos("d5"), Piece::Pawn, Color::Black,
                      Piece::None, Color::Black, Move::Flags::None));
    p.apply_move(Move(to_pos("d2"), to_pos("d4"), Piece::Pawn, Color::White,
                      Piece::None, Color::Black, Move::Flags::None));*/
    std::cout << p.board << std::endl;
    AI ai, ai2;
    Human h, h2;
    int nop = 0;
    while (true) {
        //std::cout << PseudoLegalMoveMaskGen::generate_rook_mask(p.board, p.board._pieces[p.move_ctr % 2][Piece::Rook].find_last(), p.move_ctr % 2, 0);
        if (p.board._pieces[0][Piece::King].count() == 0 || p.board._pieces[0][Piece::King].count() == 0) {
            std::cout << "Wtf?\n";
            break;
        }
        bool check = false;
        if (PseudoLegalMoveMaskGen::in_danger(p.board, p.board._pieces[p.move_ctr % 2][Piece::King].find_first(), p.move_ctr % 2)) {
            std::cout << "Check!\n" << std::endl;
            check = true;
        }
        MoveList ml = LegalMoveGen::generate(p, p.move_ctr % 2, 0);
        /*if (ml.size() == 0)
            break;*/

        Move m;
        if (p.move_ctr % 2 == 0) {
            m = ai.getMove(p, 0, 0, 30);
        } else {
            m = ai2.getMove(p, 1, 100, 100);
        }
        if (m.type == Piece::None) {
            if (nop) {

            }

            else {
                //std::cout << "Draw\n";
                //break;
            }
            //p.update_ctr();
            //p.update_fifty_moves_ctr(0);
        }
        else {
            std::cout << "Move: " << to_str(m.from) << to_str(m.to) << std::endl;
            p.apply_move(m);
            std::cout << p.board << std::endl;
        }
        if ((PseudoLegalMoveMaskGen::in_danger(p.board, p.board._pieces[!(p.move_ctr % 2)][Piece::King].find_last(), !(p.move_ctr % 2)) && check) || ml.size() == 0) {
            std::cout <<rang::fg::red << "Mate! Lose: ";
            if ((p.move_ctr-1) % 2 == 1) {
                std::cout << "White.";
            } else {
                std::cout << "Black.";
            }
            std::cout << "\n" << rang::fg::reset;
            break;
        }
    }
    return 0;
}
