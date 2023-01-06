//
// Created by dmitry on 06.01.23.
//

#ifndef SHATAR_HASH_H
#define SHATAR_HASH_H

#include <functional>

#include "Board.h"

namespace __zobrist {
    static constexpr uint64_t __seed = 0x98f107;
    static constexpr uint64_t __multiplier = 0x71abc9;
    static constexpr uint64_t __summand = 0xff1b3f;

    static consteval uint64_t next_hash(uint64_t hash) {
        return __multiplier * hash + __summand;
    }

    static consteval std::array<std::array<std::array<uint64_t ,6>, 2>, 64> precalc_hash() {
        std::array<std::array<std::array<uint64_t, 6>, 2>, 64> constants{};
        uint64_t prev = __seed;
        for (size_t bit = 0; bit < 64; ++bit) {
            for (size_t side = 0; side < 2; ++side) {
                for (size_t pc = 0; pc < 6; ++pc, prev = next_hash(prev)) {
                    constants[bit][side][pc] = prev;
                }
            }
        }
        return constants;
    }

    static constexpr auto hashes = precalc_hash();
    static constexpr uint64_t black = next_hash(hashes[63][1][5]);
}


template<>
struct std::hash<Board> {
    static constexpr size_t invert(size_t hash) {
        return hash ^ __zobrist::black;
    }

    static constexpr size_t put_piece(size_t hash, size_t square, size_t side, size_t piece) {
        return hash ^ (__zobrist::hashes[square][side][piece]);
    }

    size_t operator()(const Board&, bool) const noexcept;
};

#endif //SHATAR_HASH_H
