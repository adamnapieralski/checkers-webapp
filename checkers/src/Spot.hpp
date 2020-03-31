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
    Spot(int x, int y);

    int getX();
    int getY();
    // Spot(std::string name);
    // Spot(int x, int y, Piece& piece);
    std::string cvtPositionToName(int x, int y);
    bool isPositionValid(int x, int y);
    bool isDark();
    bool isFree();

    void setPiece(Piece *piece);

    friend std::ostream& operator<<(std::ostream& os, const Spot& s);

    // Piece* getPiece();

private:
    int x_, y_;
    std::string name_; // e.g. e4, f6
    bool isDark_;

    Piece* piece_;
};

#endif  // SPOT_HPP