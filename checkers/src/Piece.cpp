#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"

Piece::Piece(Position pos, bool isWhite) {
    pos_ = pos;
    isWhite_ = isWhite;
}

Piece::Piece(Spot &spot, bool isWhite) {
    pos_ = spot.getPosition();
    isWhite_ = isWhite;
    spot.setPiece(this);
}

bool Piece::isWhite() {
    return isWhite_;
}