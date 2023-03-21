//
// Created by dmitry on 02.01.23.
//

#ifndef SHATAR_BITBOARD_H
#define SHATAR_BITBOARD_H

#include <bitset>
#include <array>
#include <rang.hpp>
#include <iomanip>

static constexpr size_t MAGIC = 0x03f79d71b4cb0a89;

/**
 * Implementation of the Bitboard
 */

class Bitboard {
    std::bitset<64> _b;

    static constexpr std::array<size_t, 64> _BST = {
            0, 47, 1, 56, 48, 27, 2, 60,
            57, 49, 41, 37, 28, 16, 3, 61,
            54, 58, 35, 52, 50, 42, 21, 44,
            38, 32, 29, 23, 17, 11, 4, 62,
            46, 55, 26, 59, 40, 36, 15, 53,
            34, 51, 20, 43, 31, 22, 10, 45,
            25, 39, 14, 33, 19, 30, 9, 24,
            13, 18, 8, 12, 7, 6, 5, 63
    };

public:


    Bitboard() = default;

    explicit Bitboard(std::bitset<64> &&other) { _b = other; }

    explicit Bitboard(const std::string &s) { _b = std::bitset<64>(s); }

    explicit Bitboard(size_t val) { _b = std::bitset<64>(val); }

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

    [[nodiscard]] bool test(size_t i) const {
        if (i > 63)
            return 0;
        return _b.test(i);
    }

    void set(size_t i) {
        if (i < 64)
        _b.set(i);
    }

    void reset(size_t i) {
        if (i < 64)
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

    [[nodiscard]] size_t count() const noexcept {
        return _b.count();
    }

    size_t find_last() {
        return _BST[((_b.to_ullong() ^ (_b.to_ullong() - 1)) * MAGIC) >> 58];
    }

    size_t find_first();

    friend std::ostream& operator<<(std::ostream&os, Bitboard b);
};

namespace BitboardColumns {
    static std::array<Bitboard, 8> calc_columns() {
        std::array<Bitboard, 8> columns{};

        for (uint8_t x = 0; x < 8; x = x + 1) {
            for (uint8_t y = 0; y < 8; y = y + 1) columns[x].set( y * 8 + x);
        }

        return columns;
    }


    static std::array<Bitboard, 8> Columns = calc_columns();


    static std::array<Bitboard, 8> calc_inversion_columns() {
        std::array<Bitboard, 8> inversion_columns{};

        for (uint8_t i = 0; i < 8; i = i + 1) inversion_columns[i] = ~Columns[i];

        return inversion_columns;
    }


    static std::array<Bitboard, 8> InversionColumns = BitboardColumns::calc_inversion_columns();
}

#endif //SHATAR_BITBOARD_H
