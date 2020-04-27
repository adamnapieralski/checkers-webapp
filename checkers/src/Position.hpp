/**
 * @file Position.hpp
 * @brief Header file for Position structure, representing piece's position on the board.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

#define BOARD_SIZE 8

struct Position {
    int x, y;
    Position() : x(0), y(0) {};
    Position(int setX, int setY) : x(setX), y(setY) {};

    bool isValid() const {
        if (x >= 0 && x < BOARD_SIZE && y >=0 && y < BOARD_SIZE) return true;
        else return false;
    }

    bool isLastRow(bool isUser) const {
        if ((isUser && y == BOARD_SIZE - 1) || (!isUser && y == 0)) return true;
        else return false;
    }

    bool operator==(Position &p) const {
        if (x == p.x && y == p.y) return true;
        else return false;
    }

    bool operator!=(Position &p) const{
        if (x != p.x || y != p.y) return true;
        else return false;
    }

};

inline bool operator==( const Position &a, const Position &b ){
    if (a.x == b.x && a.y == b.y) return true;
    return false;
}

#endif // POSITION_HPP
