#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Board.hpp"

// Piece::Piece(Position pos, bool isWhite) {
//     pos_ = pos;
//     isWhite_ = isWhite;
// }

Piece::Piece(bool isWhite, Position pos, Board& board) {

    isWhite_ = isWhite;
    pos_ = pos;
    if(isWhite)
        board.placePiece(pos_, WhitePawn);
    else board.placePiece(pos_, BlackPawn);
}

bool Piece::isWhite() { return isWhite_;    }

Position Piece::getPosition() { return pos_;    }

/*bool Piece::isOnSameDiagonal(Piece& piece) {
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
}*/

// std::vector<Piece> Piece::piecesAbleToCapture() {

// }
