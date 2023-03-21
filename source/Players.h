//
// Created by dmitry on 08.03.23.
//

#ifndef SHATAR_PLAYERS_H
#define SHATAR_PLAYERS_H

#include <atomic>
#include <iostream>
#include <chrono>
#include <future>
#include <unistd.h>
#include <iomanip>
#include <rang.hpp>

#include "Board.h"
#include "Position.h"
#include "HashTable.h"
#include "LegalMoveGen.h"
#include "MoveSort.h"

#define nsecs std::chrono::high_resolution_clock::now().time_since_epoch().count()

class Player {
public:
    virtual Move getMove(const Position &p, size_t side, int min_time, int max_time) { return {}; }

    //virtual Board presentState();
    Player() = default;
};

class Human : public Player {
public:
    Human() = default;

    Move getMove(const Position &p, size_t side, int min_time, int max_time) override;

    //void presentMove(const Position &);
};

class AI : public Player {
private:

    static std::tuple<int, Move>
    best_move(const Position &position, size_t side, int depth, HashTable &ht);

    static std::tuple<int, Move>
    alpha_beta_min(Position position, int alpha, int beta, int depth_left, int depth_current,
                   HashTable &ht);

    static std::tuple<int, Move>
    alpha_beta_max(Position position, int alpha, int beta, int depth_left, int depth_current,
                   HashTable &ht);

    static int
    alpha_beta_min_only_captures(const Position &position, int alpha, int beta, int depth_current);

    static int
    alpha_beta_max_only_captures(const Position &position, int alpha, int beta, int depth_current);

    static constexpr int MIN = -1e9;
    static constexpr int MAX = 1e9;

public:

    AI() = default;

    Move getMove(const Position &p, size_t side, int min_time, int max_time) override;
};


#endif