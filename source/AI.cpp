//
// Created by dmitry on 20.03.23.
//

#include "Players.h"

static long long evaluated;
static int maximal_depth;
static int ht_cutoffs;

static std::atomic<bool> stop_search;

std::tuple<int, Move> AI::best_move(const Position &position, bool side, int depth, HashTable &ht) {
    if (side == Color::White)
        return AI::alpha_beta_max(position, AI::MIN, AI::MAX, depth, 0, ht);
    return AI::alpha_beta_min(position, AI::MIN, AI::MAX, depth, 0, ht);
}

std::tuple<int, Move>
AI::alpha_beta_min(Position position, int alpha, int beta, int depth_left, int depth_current, HashTable &ht) {
    if (stop_search)
        return std::make_tuple(0, Move());
    if (depth_current > maximal_depth)
        maximal_depth = depth_current;

    if (depth_left == 0)
        return std::make_tuple(AI::alpha_beta_min_only_captures(position, alpha, beta, depth_current), Move());

    if (position.fifty_moves_ctr >= 50 || position.recent_history.getRepetitionsCount(position.hash) >= 3)
        return std::make_tuple(0, Move());

    MoveList moves = LegalMoveGen::generate(position, Color::Black);
    //moves = MoveSort::sort(position.board, moves);
    Move move;
    Move best_move;
    uint8_t best_move_index;

    bool in_check = PseudoLegalMoveMaskGen::in_danger(position.board,
                                                      position.board._pieces[Color::Black][Piece::King].find_last(),
                                                      Color::Black);

    if (moves.size() == 0) {
        if (in_check)
            return std::make_tuple(AI::MAX - depth_current, Move());
        return std::make_tuple(0, Move());
    }

    int32_t evaluation;

    Position copy;

    uint8_t ht_result = ht.find(position.hash);

    for (uint8_t i = 0; i < moves.size(); i = i + 1) {
        if (ht_result >= moves.size()) move = moves[i];
        else {
            if (i == 0) move = moves[ht_result];
            else {
                if (i == ht_result)
                    move = moves[0];
                else
                    move = moves[i];
            }
        }

        copy = position;
        copy.apply_move(move);
        evaluation = std::get<0>(AI::alpha_beta_max(copy, alpha, beta, depth_left - !in_check, depth_current + 1, ht));

        if (evaluation <= alpha) {
            if (ht_result >= moves.size() || i != 0)
                ht.add_entry(position.hash, {depth_left, best_move_index});
            else
                ht_cutoffs = ht_cutoffs + 1;
            return std::make_tuple(alpha, best_move);
        }
        if (evaluation < beta) {
            best_move = move;
            best_move_index = i;
            beta = evaluation;
        }
    }

    ht.add_entry(position.hash, {depth_left, best_move_index});
    return std::make_tuple(beta, best_move);
}

std::tuple<int, Move>
AI::alpha_beta_max(Position position, int alpha, int beta, int depth_left, int depth_current, HashTable &ht) {
    if (stop_search)
        return std::make_tuple(0, Move());
    if (depth_current > maximal_depth)
        maximal_depth = depth_current;

    if (depth_left == 0)
        return std::make_tuple(AI::alpha_beta_max_only_captures(position, alpha, beta, depth_current), Move());

    if (position.fifty_moves_ctr >= 50 || position.recent_history.getRepetitionsCount(position.hash) >= 3)
        return std::make_tuple(0, Move());

    MoveList moves = LegalMoveGen::generate(position, Color::White);
    //moves = MoveSort::sort(position.board, moves);
    Move move;
    Move best_move;
    uint8_t best_move_index;

    bool in_check = PseudoLegalMoveMaskGen::in_danger(position.board,
                                                      position.board._pieces[Color::White][Piece::King].find_last(),
                                                      Color::White);

    if (moves.size() == 0) {
        if (in_check)
            return std::make_tuple(AI::MIN + depth_current, Move());
        return std::make_tuple(0, Move());
    }

    int32_t evaluation;

    Position copy;

    uint8_t tt_result = ht.find(position.hash);

    for (uint8_t i = 0; i < moves.size(); i = i + 1) {
        if (tt_result >= moves.size()) move = moves[i];
        else {
            if (i == 0) move = moves[tt_result];
            else {
                if (i == tt_result) move = moves[0];
                else move = moves[i];
            }
        }

        copy = position;
        copy.apply_move(move);
        evaluation = std::get<0>(AI::alpha_beta_min(copy, alpha, beta, depth_left - !in_check, depth_current + 1, ht));

        if (evaluation >= beta) {
            if (tt_result >= moves.size() || i != 0)
                ht.add_entry(position.hash, {depth_left, best_move_index});
            else
                ht_cutoffs = ht_cutoffs + 1;
            return std::make_tuple(beta, best_move);
        }
        if (evaluation > alpha) {
            best_move = move;
            best_move_index = i;
            alpha = evaluation;
        }
    }

    ht.add_entry(position.hash, {depth_left, best_move_index});
    return std::make_tuple(alpha, best_move);
}

int AI::alpha_beta_min_only_captures(const Position &position, int alpha, int beta, int depth_current) {
    if (stop_search)
        return 0;
    if (depth_current > maximal_depth)
        maximal_depth = depth_current;

    int32_t evaluation = Static::evaluate(position.board);
    evaluated = evaluated + 1;

    if (evaluation <= alpha)
        return alpha;
    if (evaluation < beta)
        beta = evaluation;

    MoveList moves = LegalMoveGen::generate(position, Color::Black, true);
    //moves = MoveSort::sort(position.board, moves);

    Move move;

    Position copy;

    for (uint8_t i = 0; i < moves.size(); i = i + 1) {
        move = moves[i];

        copy = position;
        copy.apply_move(move);
        evaluation = AI::alpha_beta_max_only_captures(copy, alpha, beta, depth_current + 1);

        if (evaluation <= alpha)
            return alpha;
        if (evaluation < beta)
            beta = evaluation;
    }

    return beta;
}

int AI::alpha_beta_max_only_captures(const Position &position, int alpha, int beta, int depth_current) {
    if (stop_search)
        return 0;
    if (depth_current > maximal_depth)
        maximal_depth = depth_current;

    int32_t evaluation = Static::evaluate(position.board);
    evaluated = evaluated + 1;

    if (evaluation >= beta)
        return beta;
    if (evaluation > alpha)
        alpha = evaluation;

    MoveList moves = LegalMoveGen::generate(position, Color::White, true);
    //moves = MoveSort::sort(position.board, moves);
    Move move;

    Position copy;

    for (uint8_t i = 0; i < moves.size(); i = i + 1) {
        move = moves[i];


        copy = position;
        copy.apply_move(move);
        evaluation = AI::alpha_beta_min_only_captures(copy, alpha, beta, depth_current + 1);

        if (evaluation >= beta)
            return beta;
        if (evaluation > alpha)
            alpha = evaluation;
    }

    return alpha;
}

Move AI::getMove(const Position &p, bool side, int min_time, int max_time) {
    std::cout << std::endl;
    Static::evaluate(p.board);

    int64_t time_start = nsecs;
    stop_search = false;
    HashTable ht;

    std::cout << rang::fg::green << "Search started." << std::endl;

    int32_t best_move_evaluation;
    Move best_move;
    std::future<std::tuple<int32_t, Move>> best_move_thread;

    bool update_best_move;

    for (int32_t i = 1; i < 1e+3; i = i + 1) {
        evaluated = 0;
        maximal_depth = 0;
        ht_cutoffs = 0;

        best_move_thread = std::async(AI::best_move, p, side, i, std::ref(ht));

        update_best_move = true;
        while (best_move_thread.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            if ((nsecs - time_start) / (int32_t)1e+6 >= max_time) {
                update_best_move = false;
                break;
            }
            usleep(20000);
        }

        if (update_best_move || i == 1) {
            //std::tie(best_move_evaluation, best_move) = best_move_thread.get();
            auto bm = best_move_thread.get();
            std::tie(best_move_evaluation, best_move) = bm;
        } else {
            stop_search = true;
            break;
        }

        std::cout << "Base depth: " << std::setw(4) << i << ". Maximal depth: " << std::setw(4) << maximal_depth << ". Evaluation: " << std::setw(6) << (float)best_move_evaluation / 100.0f << " pawns. Evaluated (this iteration): " << std::setw(10) << evaluated << ". TT cutoffs (this iteration): " << std::setw(10) << ht_cutoffs << ". Time (full search): " << std::setw(10) << (nsecs - time_start) / (int32_t)1e+6 << " ms." << std::endl;

        if (best_move_evaluation > AI::MAX - 2000 || best_move_evaluation < AI::MIN + 2000)
            break;
    }

    usleep(std::max((int64_t)0, (min_time - (nsecs - time_start) / (int64_t)1e+6) * (int64_t)1e+3));

    std::cout << "Search finished." << std::endl << rang::fg::reset;

    return best_move;
}

