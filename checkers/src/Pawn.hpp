#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
    using Piece::Piece;
    
public:

    std::ostream& print(std::ostream&) override;
    void canCapture(std::vector<Move> &moves, Board board, Move current) override;
    std::vector<Move> getValidMoves(Board &board) override;

};

#endif  // PAWN_HPP