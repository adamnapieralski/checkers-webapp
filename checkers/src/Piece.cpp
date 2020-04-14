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

bool Piece::isOnSameDiagonal(Piece& piece) {
    // on \ diagonal
    if (getPosition().x + getPosition().y == piece.getPosition().x + piece.getPosition().y)
        return true;

    // on / diagonal
    if (abs(getPosition().x - piece.getPosition().x) == abs(getPosition().y - piece.getPosition().y))
        return true;

    return false;
}


// int Piece::radiusDistance(Piece& piece) {
//     if (!this->isOnSameDiagonal(piece)) return -1;

//     return std::abs(this->pos_.x - piece.pos_.x);
// }

Position Piece::positionDistance(Position pos) {
    return Position(pos.x - getPosition().x, pos.y - getPosition().y);
}