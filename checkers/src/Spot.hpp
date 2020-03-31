#ifndef SPOT_HPP
#define SPOT_HPP

#include <string>
#include <array>
#include <iostream>

#include "Piece.hpp"

class Piece;

class Spot {
public:
    Spot();
    Spot(Position pos);

    Position getPosition();
    // Spot(std::string name);
    // Spot(int x, int y, Piece& piece);
    std::string cvtPositionToName(Position pos);
    bool isPositionValid(Position pos);
    bool isDark();
    bool isFree();

    void setPiece(Piece *piece);

    friend std::ostream& operator<<(std::ostream& os, const Spot& s);

    // Piece* getPiece();

private:
    Position pos_;
    std::string name_; // e.g. e4, f6
    bool isDark_;


    Piece* piece_;
};

#endif  // SPOT_HPP