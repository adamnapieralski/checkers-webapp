#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;
    
    std::ostream& print(std::ostream&);
};

#endif  // KING_HPP