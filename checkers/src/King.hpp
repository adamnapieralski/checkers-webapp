#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;

public:
    std::ostream& print(std::ostream&);
    bool canCapture(std::vector<Move> &moves, Board board, Move current) override;
};

#endif  // KING_HPP