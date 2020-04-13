#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;

public:
    King(Position pos, bool isWhite, Board& board);
    std::vector<Move> getValidMoves(Board& board, bool mustCapture=false) override;
    bool canCapture(Piece& piece,  Board &board) override;

    std::ostream& print(std::ostream&);
};

#endif  // KING_HPP