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
    int pieceCoordSum = piece.getPosition().x + piece.getPosition().y;
    
    // on \ diagonal
    if (thisCoordSum == pieceCoordSum) return true;
    
    int thisCoordDiff = std::abs(this->pos_.x - this->pos_.y);
    int pieceCoordDiff = std::abs(piece.getPosition().x - piece.getPosition().y);

    // on / diagonal
    if (thisCoordDiff == pieceCoordDiff) return true;

    return false;
}

int Piece::radiusDistance(Piece& piece) {
    if (!this->isOnSameDiagonal(piece)) return -1;

    return std::abs(this->pos_.x - piece.getPosition().x);
}

// std::vector<Piece> Piece::piecesAbleToCapture() {

// }
