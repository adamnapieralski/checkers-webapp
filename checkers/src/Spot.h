#ifndef Spot_h
#define Spot_h

#include <string>
#include <array>
#include "Piece.h"

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

    // Piece* getPiece();

private:
    int x_, y_;
    std::string name_; // e.g. e4, f6
    bool isDark_;

    Piece* piece_;
};

#endif