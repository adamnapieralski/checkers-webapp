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

#define BOARD_SIZE 8

class Position {
public:
    int x, y;
    Position();
    Position(int setX, int setY);

    bool isValid() const;
    bool isLastRow(bool isUser) const;

    bool operator==(const Position& p) const;
    bool operator!=(const Position& p) const;
};

#endif // POSITION_H
