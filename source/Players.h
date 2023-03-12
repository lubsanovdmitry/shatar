//
// Created by dmitry on 08.03.23.
//

#ifndef SHATAR_PLAYERS_H
#define SHATAR_PLAYERS_H

#include "Board.h"
#include "Position.h"

class Player {
public: 
    virtual Move getMove(const Position&);
    //virtual Board presentState();
    Player () = default;
};

class Human : public Player {
public:
    Move getMove(const Position&) override;
    void presentMove(const Position&);
};

class AI : public Player {
private:

public:
    Move getMove(const Position&) override;
};

#endif