#include <iostream>
#include <string>

#include "Board.h"
#include "Hash.h"


int main(int argc, char **argv) {
    std::string s;
    std::cin >> s;
    Board b(s);
    std::cout << b;
    std::cout << std::hash<Board>{}(b, 0);
    std::cin >> s;
    b = Board(s);
    std::cout << b;
    std::cout << std::hash<Board>{}(b, 0);
    return 0;
}
