#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Board.hpp"

// Piece::Piece(Position pos, bool isWhite) {
//     pos_ = pos;
//     isWhite_ = isWhite;
// }

Piece::Piece(Position pos, bool isWhite, bool isUser) :
    pos_(pos), isWhite_(isWhite), isUser_(isUser) {}

bool Piece::isWhite() { return isWhite_;    }

bool Piece::isUser() {  return isUser_; }

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

void Piece::changePosition(Position pos){
    pos_ = pos;
}

bool Piece::isSameColor(PieceName pn) {
    if ( (isWhite_ && ( pn == WHITE_PAWN  || pn == WHITE_KING ) )
        || (!isWhite_ && (pn == BLACK_PAWN || pn == BLACK_KING) ) )
        return true;
    else return false;
}

bool Piece::isDiffColor(PieceName pn) {
    if ( (isWhite_ && ( pn == BLACK_PAWN || pn == BLACK_KING) )
        || (!isWhite_ && (pn == WHITE_PAWN || pn == WHITE_KING) ) )
        return true;
    else return false;
}
