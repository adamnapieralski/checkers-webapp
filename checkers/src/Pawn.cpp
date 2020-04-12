#include "Pawn.hpp"
#include "Board.hpp"

std::vector<Move> Pawn::getValidMoves(Board& board) {
    return std::vector<Move>();
}

bool Pawn::canCapture(Piece& piece, Board &board) {
    if (this->isWhite() == piece.isWhite()) return false;

    Position diff = positionDistance(piece);
    if (abs(diff.x) != 1 || abs(diff.y) != 1) return false;

    int newX = piece.getPosition().x + diff.x;
    int newY = piece.getPosition().y + diff.y;
    Position newPos(newX, newY);

    if (!newPos.isPositionValid()) return false;
    if (board.getBoard()[newX][newY] == Empty) return true;
    else return false;
}


std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}