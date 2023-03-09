//
// Created by dmitry on 08.03.23.
//

#ifndef SHATAR_PLAYERS_H
#define SHATAR_PLAYERS_H

#include "Board.h"

class Player {
public: 
    virtual int getMove(const Board&);
    //virtual Board presentState();
    Player () = default;
};

class Human : public Player {
public:
    int getMove(const Board&);
    void presentMove(const Board&);
};

class AI : public Player {
private:

public:
    int getMove(const Board&);
};

#endif