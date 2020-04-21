#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;

public:
    King(Position pos, bool isWhite, bool isUser, Board& board);

    void getCaptureMoves(std::vector<Move> &moves, Board board, Move current);
    std::vector<Move> getValidMoves(Board& board) override;

    std::ostream& print(std::ostream&);
};

#endif  // KING_HPP