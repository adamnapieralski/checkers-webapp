#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <vector>

#include "Position.hpp"
#include "Move.hpp"
#include "Board.hpp"

class Spot;

// to resolve: class Piece has virtual funcs and accessible non-virtual destructor
class Piece {
public:
    // Piece(Position pos, bool isWhite, Board* board);
    Piece(Position pos, bool isWhite);
    virtual ~Piece() {};

    bool isWhite();
    
    Position getPosition();

    bool isOnSameDiagonal(Piece& piece);
    // int radiusDistance(Piece& piece);
    Position positionDistance(Piece& piece);

    bool isSameColor(PieceName pn);
    bool isDiffColor(PieceName pn);
    
    virtual std::vector<Move> getValidMoves(Board& board, bool mustCapture=false) = 0;

    virtual bool canCapture(Piece& piece,  Board &board) = 0;
    

    virtual std::ostream& print(std::ostream& os) = 0;


private:
    Position pos_;
    bool isWhite_;

};

#endif  // PIECE_HPP