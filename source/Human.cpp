//
// Created by dmitry on 21.03.23.
//

#include "Players.h"

Move Human::getMove(const Position &p, bool side, int min_time, int max_time) {
    MoveList ml = LegalMoveGen::generate(p, side, 0);
    std::string s;
    std::cin >> s;
    std::string s1 = s.substr(0, 2), s2 = s.substr(2);
    size_t from = to_pos(s1), to = to_pos(s2);
    Move m;
    for (int i = 0; i < ml.size(); ++i) {
        if (ml[i].from == from && ml[i].to == to) {
            m = ml[i];
            if (ml[i].flag != Move::Flags::None) {
                std::cout << rang::fg::red << "Promotion? " << rang::fg::reset;
                char c;
                std::cin >> c;
                c = tolower(c);
                switch (c) {
                    case 'q':
                        m.flag = Move::Flags::PromotedQueen;
                        break;
                    case 'r':
                        m.flag = Move::Flags::PromotedRook;
                        break;
                    case 'k':
                        m.flag = Move::Flags::PromotedKnight;
                        break;
                    case 'b':
                        m.flag = Move::Flags::PromotedBishop;
                        break;
                }
            }
            break;
        }
    }
    return m;
}