#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include "Spot.hpp"

class Spot;

class Piece {
public:
    Piece(int x, int y, bool isWhite);
    Piece(Spot &spot, bool isWhite);

    bool isWhite();

    virtual std::ostream& print(std::ostream& os) = 0;


private:
    int x_, y_;
    bool isWhite_;



};

#endif  // PIECE_HPP