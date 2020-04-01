#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Board.hpp"

// Piece::Piece(Position pos, bool isWhite) {
//     pos_ = pos;
//     isWhite_ = isWhite;
// }

Piece::Piece(Spot &spot, bool isWhite) {
    spot_ = &spot;
    pos_ = spot.getPosition();
    isWhite_ = isWhite;
    spot.setPiece(this);
}

bool Piece::isWhite() { return isWhite_;    }

Position Piece::getPosition() { return pos_;    }

bool Piece::isOnSameDiagonal(Piece& piece) {
    int thisCoordSum = this->pos_.x + this->pos_.y;
    int pieceCoordSum = piece.pos_.x + piece.pos_.y;

    // on \ diagonal
    if (thisCoordSum == pieceCoordSum) return true;
    // on / diagonal
    if ((this->pos_.x - piece.pos_.x) * 2 + piece.pos_.x == this->pos_.x) return true;

    return false;
}

int Piece::radiusDistance(Piece& piece) {
    if (!this->isOnSameDiagonal(piece)) return -1;

    return std::abs(this->pos_.x - piece.pos_.x);
}

// std::vector<Piece> Piece::piecesAbleToCapture() {

// }
