#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;

public:
    std::ostream& print(std::ostream&);
    bool canCapture(Piece& piece,  Board &board) override;
};

#endif  // KING_HPP