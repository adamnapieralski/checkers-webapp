#include "Piece.h"

Piece::Piece(int x, int y, bool isWhite) {
    x_ = x;
    y_ = y;
    isWhite_ = isWhite;
}

Piece::Piece(Spot &spot, bool isWhite) {
    x_ = spot.getX();
    y_ = spot.getY();
    isWhite_ = isWhite;
    spot.setPiece(this);
}

bool Piece::isWhite() {
    return isWhite_;
}