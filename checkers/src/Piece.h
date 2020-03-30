#ifndef Piece_h
#define Piece_h

#include <string>
#include "Spot.h"

class Spot;

class Piece {
public:
    Piece(int x, int y, bool isWhite);
    Piece(Spot &spot, bool isWhite);

    bool isWhite();

private:
    int x_, y_;
    bool isWhite_;

};

#endif