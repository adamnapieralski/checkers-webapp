#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <vector>

#include "Position.hpp"
#include "Spot.hpp"

class Spot;

// to resolve: class Piece has virtual funcs and accessible non-virtual destructor
class Piece {
public:
    // Piece(Position pos, bool isWhite, Board* board);
    Piece(Spot &spot, bool isWhite);
    virtual ~Piece() {};

    bool isWhite();
    
    Position getPosition();

    bool isOnSameDiagonal(Piece& piece);
    int radiusDistance(Piece& piece);

    virtual bool canCapture(Piece& piece) = 0;
    

    virtual std::ostream& print(std::ostream& os) = 0;

protected:
    Spot* spot_;

private:
    Position pos_;
    bool isWhite_;




};

#endif  // PIECE_HPP