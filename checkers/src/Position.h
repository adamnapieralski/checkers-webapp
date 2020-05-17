/**
 * @file Position.h
 * @brief Header file for Position structure, representing piece's position on the board.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <map>

#define BOARD_SIZE 8

class Position {
public:
    int x, y;
    Position();
    Position(int setX, int setY);

    bool isValid() const;
    bool isLastRow(bool isUser) const;
    bool isZero() const;

    /**
     * return position made of 1/-1 when abs of x and y are equal
     * else return zero position
     */
    Position getUnitPosition() const;

    bool operator==(const Position& p) const;
    bool operator!=(const Position& p) const;

    Position& operator+=(const Position& rhs);
    Position& operator-=(const Position& rhs);
    friend Position operator+(Position lhs, const Position& rhs);
    friend Position operator-(Position lhs, const Position& rhs);
};

#endif // POSITION_H
