#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;

public:
    King(Position pos, bool isWhite, bool isUser, Board& board);

    void captureMoves(std::vector<Move> &moves, Board board, Move current) override;
    std::vector<Move> getCaptureMoves(Board& board) override;
    std::vector<Move> getValidMoves(Board& board) override;

    std::ostream& print(std::ostream&);
};

#endif  // KING_HPP