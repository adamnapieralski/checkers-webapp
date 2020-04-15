#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
    using Piece::Piece;
    
public:
    Pawn(Position pos, bool isWhite, Board& board);

    std::vector<Move> getValidMoves(Board& board, bool mustCaputer=false) override;
    bool canCapture(Piece& piece,  Board &board) override;

    std::ostream& print(std::ostream&) override;
};

#endif  // PAWN_HPP