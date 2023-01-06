#include <iostream>
#include <string>

#include "Board.h"


int main(int argc, char **argv) {
    std::string s;
    std::cin >> s;
    Board b(s);
    for (size_t bit = 0; bit < 64; ++bit) {
        if (b.look_pieces(Color::White, Piece::Pawn).test(bit)) std::cout << 'P';
        else if (b.look_pieces(Color::White, Piece::Rook).test(bit)) std::cout << 'R';
        else if (b.look_pieces(Color::White, Piece::Knight).test(bit)) std::cout << 'N';
        else if (b.look_pieces(Color::White, Piece::Bishop).test(bit)) std::cout << 'B';
        else if (b.look_pieces(Color::White, Piece::Queen).test(bit)) std::cout << 'Q';
        else if (b.look_pieces(Color::White, Piece::King).test(bit)) std::cout << 'K';
        else if (b.look_pieces(Color::Black, Piece::Pawn).test(bit)) std::cout << 'p';
        else if (b.look_pieces(Color::Black, Piece::Rook).test(bit)) std::cout << 'r';
        else if (b.look_pieces(Color::Black, Piece::Knight).test(bit)) std::cout << 'n';
        else if (b.look_pieces(Color::Black, Piece::Bishop).test(bit)) std::cout << 'b';
        else if (b.look_pieces(Color::Black, Piece::Queen).test(bit)) std::cout << 'q';
        else if (b.look_pieces(Color::Black, Piece::King).test(bit)) std::cout << 'k';
        else std::cout << ' ';
        if ((bit + 1) % 8 == 0)
            std::cout << std::endl;
    }
    return 0;
}
