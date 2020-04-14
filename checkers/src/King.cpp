#include "King.hpp"

bool King::canCapture(std::vector<Move> &moves, Board board, Move current){
    /*if (this->isWhite() == piece.isWhite()) return false;
    // if not on same diagonal
    if (isOnSameDiagonal(piece)) return false;

    Position diff = positionDistance(piece);
    Position thisPos = this->getPosition(), piecePos = piece.getPosition();

    int stepX = diff.x / abs(diff.x), stepY = diff.y / abs(diff.y);
    for (int i = 1; i < abs(diff.x); ++i) {
        if (board.getBoard()[thisPos.x + i * stepX][thisPos.y + i * stepY] != Empty)
            return false;
    }

    int newX = piecePos.x + stepX;
    int newY = piecePos.y + stepY;
    Position newPos(newX, newY);

    if (!newPos.isPositionValid()) return false;
    if (board.getBoard()[newX][newY] == Empty) return true;
    else return false;*/
}


std::ostream& King::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}
