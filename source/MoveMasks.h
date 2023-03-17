//
// Created by dmitry on 15.03.23.
//

#ifndef SHATAR_MOVEMASKS_H
#define SHATAR_MOVEMASKS_H

#include "Bitboard.h"

namespace KingMasks {
    static size_t abs_subtract(size_t left, size_t right) {
        if (left >= right) return left - right;
        return right - left;
    }

    static std::array<Bitboard, 64> calc_masks() {
        std::array<Bitboard, 64> masks{};

        size_t dx;
        size_t dy;

        for (size_t x0 = 0; x0 < 8; ++x0) {
            for (size_t y0 = 0; y0 < 8; ++y0) {
                for (size_t x1 = 0; x1 < 8; ++x1) {
                    for (size_t y1 = 0; y1 < 8; ++y1) {
                        dx = abs_subtract(x0, x1);
                        dy = abs_subtract(y0, y1);

                        if (dx <= 1 and dy <= 1)
                            masks[y0 * 8 + x0].set(y1 * 8 + x1);
                    }
                }
            }
        }

        return masks;
    }


    static std::array<Bitboard, 64> Masks = calc_masks();
}

namespace KnightMasks {
    static size_t abs_subtract(size_t left, size_t right) {
        if (left >= right) return left - right;
        return right - left;
    }
    static std::array<Bitboard, 64> calc_masks() {
        std::array<Bitboard, 64> masks{};

        size_t dx;
        size_t dy;

        for (size_t x0 = 0; x0 < 8; ++x0) {
            for (size_t y0 = 0; y0 < 8; ++y0) {
                for (size_t x1 = 0; x1 < 8; ++x1) {
                    for (size_t y1 = 0; y1 < 8; ++y1) {
                        dx = abs_subtract(x0, x1);
                        dy = abs_subtract(y0, y1);

                        if ((dx == 2 and dy == 1) or (dx == 1 and dy == 2))
                            masks[y0 * 8 + x0].set(y1 * 8 + x1);
                    }
                }
            }
        }

        return masks;
    }


    static std::array<Bitboard, 64> Masks = calc_masks();
}

namespace SlidersMasks {
    struct Direction {
        static constexpr int North = 0;
        static constexpr int South = 1;
        static constexpr int West = 2;
        static constexpr int East = 3;

        static constexpr int NorthWest = 4;
        static constexpr int NorthEast = 5;
        static constexpr int SouthWest = 6;
        static constexpr int SouthEast = 7;
    };


    static Bitboard calc_mask(size_t p, int direction) {
        Bitboard mask = Bitboard(0);

        int8_t x = p % 8;
        int8_t y = p / 8;

        for (;;) {
            switch (direction) {
                case SlidersMasks::Direction::North: y = y + 1; break;
                case SlidersMasks::Direction::South: y = y - 1; break;
                case SlidersMasks::Direction::West: x = x - 1; break;
                case SlidersMasks::Direction::East: x = x + 1; break;

                case SlidersMasks::Direction::NorthWest: y = y + 1; x = x - 1; break;
                case SlidersMasks::Direction::NorthEast: y = y + 1; x = x + 1; break;
                case SlidersMasks::Direction::SouthWest: y = y - 1; x = x - 1; break;
                case SlidersMasks::Direction::SouthEast: y = y - 1; x = x + 1; break;
            }

            if (x > 7 or x < 0 or y > 7 or y < 0) break;

            mask.set(y * 8 + x);
        }

        return mask;
    }


    static std::array<std::array<Bitboard, 8>, 64> calc_masks() {
        std::array<std::array<Bitboard, 8>, 64> masks{};

        for (uint8_t i = 0; i < 64; i = i + 1) {
            for (uint8_t j = 0; j < 8; j = j + 1) masks[i][j] = SlidersMasks::calc_mask(i, j);
        }

        return masks;
    }


    static std::array<std::array<Bitboard, 8>, 64> Masks = SlidersMasks::calc_masks();
}

#endif //SHATAR_MOVEMASKS_H
