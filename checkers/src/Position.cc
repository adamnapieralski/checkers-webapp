/**
 * @file Position.cpp
 * @brief Source file for Position structure, representing piece's position on the board.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "Position.h"

Position::Position() : x(0), y(0) {}

Position::Position(int setX, int setY) : x(setX), y(setY) {}

bool Position::isValid() const {
    if (x >= 0 && x < BOARD_SIZE && y >=0 && y < BOARD_SIZE) return true;
    else return false;
}

bool Position::isLastRow(bool isUser) const {
    if ((isUser && y == BOARD_SIZE - 1) || (!isUser && y == 0)) return true;
    else return false;
}

bool Position::operator==(const Position& p) const {
    if (x == p.x && y == p.y) return true;
    else return false;
}

bool Position::operator!=(const Position& p) const{
    if (x != p.x || y != p.y) return true;
    else return false;
}