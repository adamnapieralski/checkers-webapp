/**
 * @file Position.cc
 * @brief Source file for Position structure, representing piece's position on the board.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "Position.h"

Position::Position() : x(0), y(0) {}

Position::Position(int setX, int setY) : x(setX), y(setY) {}

/**
 * @brief This function checks if Position is valid
 * */
bool Position::isValid() const {
    if (x >= 0 && x < BOARD_SIZE && y >=0 && y < BOARD_SIZE) return true;
    else return false;
}

/**
 * @brief This function checks if Position is on the last row for Player and Piece can be upgraded
 * */
bool Position::isLastRow(bool isUser) const {
    if ((isUser && y == BOARD_SIZE - 1) || (!isUser && y == 0)) return true;
    else return false;
}


/**
 * @brief This function checks if Position is (0,0) - left bottom corner
 * */
bool Position::isZero() const {
    if (x == 0 && y == 0) {
        return true;
    }
    return false;
}


/**
* @return Position made of 1/-1 when abs of x and y are equal else return zero Position
*/
Position Position::getUnitPosition() const {
    int ux, uy;
    if (abs(x) != abs(y)) return Position(0, 0);
    if (x > 0) ux = 1;
    else if (x < 0) ux = -1;
    else ux = 0;

    if (y > 0) uy = 1;
    else if (y < 0) uy = -1;
    else uy = 0;

    return Position(ux, uy);
}

bool Position::operator==(const Position& p) const {
    if (x == p.x && y == p.y) return true;
    else return false;
}

bool Position::operator!=(const Position& p) const{
    if (x != p.x || y != p.y) return true;
    else return false;
}

Position& Position::operator+=(const Position& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Position& Position::operator-=(const Position& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Position operator+(Position lhs, const Position& rhs) {
    lhs += rhs;
    return lhs;
}

Position operator-(Position lhs, const Position& rhs) {
    lhs -= rhs;
    return lhs;
}