#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>

#include "Position.hpp"
#include "Spot.hpp"


class Spot;

// to resolve: class Piece has virtual funcs and accessible non-virtual destructor
class Piece {
public:
    Piece(Position pos, bool isWhite);
    Piece(Spot &spot, bool isWhite);
    virtual ~Piece() {};
    
    bool isWhite();

    virtual std::ostream& print(std::ostream& os) = 0;


private:
    Position pos_;
    bool isWhite_;



};

#endif  // PIECE_HPP