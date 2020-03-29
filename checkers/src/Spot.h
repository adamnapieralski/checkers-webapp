#ifndef Spot_h
#define Spot_h

#include <string>
#include "Piece.h"

class Spot {
private:
    int x, y;
    std::string name; // e.g. e4, f6

    Piece piece;

public:
    Spot(int x, int y);
    Spot(std::string name);
    Spot(int x, int y, Piece& piece);

    bool isFree();
    Piece& getPiece();
};

#endif