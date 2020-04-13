#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Board.hpp"

// Piece::Piece(Position pos, bool isWhite) {
//     pos_ = pos;
//     isWhite_ = isWhite;
// }

Piece::Piece(Position pos, bool isWhite) {
    isWhite_ = isWhite;
    pos_ = pos;
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

Position Piece::positionDistance(Piece& piece) {
    return Position(piece.getPosition().x - getPosition().x, piece.getPosition().y - getPosition().y);
}

bool Piece::isSameColor(PieceName pn) {
    if (isWhite_ && (pn == WhitePawn || pn == WhiteKing)
        || !isWhite_ && (pn == BlackPawn || pn == BlackKing))
        return true;
    else return false;
}

bool Piece::isDiffColor(PieceName pn) {
    if (isWhite_ && (pn == BlackPawn || pn == BlackKing)
        || isWhite_ && (pn == WhitePawn || pn == WhiteKing))
        return true;
    else return false;
}

