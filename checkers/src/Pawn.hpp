#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
    using Piece::Piece;
    
public:

    std::ostream& print(std::ostream&) override;

};

#endif  // PAWN_HPP