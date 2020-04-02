#include "Pawn.hpp"
#include "Board.hpp"

/*bool Pawn::canCapture(Piece& piece) {
    if (this->isWhite() == piece.isWhite()) return false;
    int dist = this->radiusDistance(piece);
    if (dist != 1) return false;

    int newX = this->getPosition().x + (piece.getPosition().x - this->getPosition().x) * 2;
    int newY = this->getPosition().y + (piece.getPosition().y - this->getPosition().y) * 2;

    Position newPos(newX, newY);
    if (!newPos.isPositionValid()) return false;
    if (spot_->getBoard()->getSpotOnPosition(newPos).isFree()) return true;
    else return false;

}*/

std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}