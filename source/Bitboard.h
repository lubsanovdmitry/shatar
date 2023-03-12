//
// Created by dmitry on 02.01.23.
//

#ifndef SHATAR_BITBOARD_H
#define SHATAR_BITBOARD_H

#include <bitset>
#include <array>

static constexpr size_t MAGIC = 0x03f79d71b4cb0a89;

/**
 * Implementation of the Bitboard
 */

class Bitboard {
    std::bitset<64> _b;

    static constexpr std::array<size_t, 64> _BST = {
            0, 47,  1, 56, 48, 27,  2, 60,
            57, 49, 41, 37, 28, 16,  3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11,  4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30,  9, 24,
            13, 18,  8, 12,  7,  6,  5, 63
    };

public:

    //explicit Bitboard(std::bitset<64> &&other) { _b = other; }
    Bitboard() = default;

    /**
     * Test a bit on the bitboard
     * @param i file
     * @param j rank
     * @return true if the bit is set
     */

    bool test(size_t i, size_t j) const {
        return _b.test(i * 8 + j);
    }

    void set(size_t i, size_t j) {
        _b.set(i * 8 + j);
    }

    void reset(size_t i, size_t j) {
        _b.reset(i * 8 + j);
    }

    bool test(size_t i) const {
        return _b.test(i);
    }

    void set(size_t i) {
        _b.set(i);
    }

    void reset(size_t i) {
        _b.reset(i);
    }

    Bitboard &operator&=(const Bitboard &other) noexcept {
        _b &= other._b;
        return *this;
    }

    Bitboard &operator|=(const Bitboard &other) noexcept {
        _b |= other._b;
        return *this;
    }

    Bitboard &operator^=(const Bitboard &other) noexcept {
        _b ^= other._b;
        return *this;
    }

    friend Bitboard operator~(Bitboard other) noexcept {
        other._b = ~other._b;
        return other;
    }

    friend Bitboard operator&(Bitboard lhs, const Bitboard &rhs) noexcept {
        lhs._b &= rhs._b;
        return lhs;
    }

    friend Bitboard operator|(Bitboard lhs, const Bitboard &rhs) noexcept {
        lhs._b |= rhs._b;
        return lhs;
    }

    friend Bitboard operator^(Bitboard lhs, const Bitboard &rhs) noexcept {
        lhs._b ^= rhs._b;
        return lhs;
    }

    bool operator==(const Bitboard &rhs) const noexcept {
        return _b == rhs._b;
    }

    bool operator!=(const Bitboard &rhs) const noexcept {
        return _b != rhs._b;
    }

    Bitboard operator<<(size_t pos) const noexcept {
        Bitboard b = *this;
        b._b <<= pos;
        return b;
    }

    Bitboard operator>>(size_t pos) const noexcept {
        Bitboard b = *this;
        b._b >>= pos;
        return b;
    }

    Bitboard &operator<<=(size_t pos) noexcept {
        _b <<= pos;
        return *this;
    }

    Bitboard &operator>>=(size_t pos) noexcept {
        _b >>= pos;
        return *this;
    }

    size_t count() const noexcept {
        return _b.count();
    }

    size_t find_first() {
        return _BST[(_b.to_ullong() ^ (_b.to_ullong() - 1)) * MAGIC];
    }

    size_t find_last();
};

#endif //SHATAR_BITBOARD_H
