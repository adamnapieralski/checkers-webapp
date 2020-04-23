#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
    using Piece::Piece;
    
public:
    Pawn(Position pos, bool isWhite, bool isUser, Board& board);

    void captureMoves(std::vector<Move> &moves, Board board, Move current) override;
    std::vector<Move> getCaptureMoves(Board& board) override;
    std::vector<Move> getValidMoves(Board& board) override;

    std::ostream& print(std::ostream&) override;
};

#endif  // PAWN_HPP