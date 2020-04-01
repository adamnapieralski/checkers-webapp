#include "Spot.hpp"
#include "Board.hpp"

Spot::Spot(Position pos, Board* board) {
    if (isPositionValid(pos)) {
        pos_ = pos;
        isDark_ = (pos.x + pos.y + 1) % 2;
        name_ = cvtPositionToName(pos);
        piece_ = nullptr;
        board_ = board;
    }
    // else maybe throw excptn
}

Position Spot::getPosition() {  return pos_;    }

Board* Spot::getBoard() {   return board_;  }

Piece* Spot::getPiece() {   return piece_;  }

bool Spot::isPositionValid(Position pos) {
    if (pos.x >= 0 && pos.x <= 8 && pos.y >=0 && pos.y <=8) return true;
    else return false;
}

bool Spot::isDark() { return isDark_; }

bool Spot::isFree() {
    if (piece_ == nullptr) return true;
    else return false;
}

void Spot::setPiece(Piece *piece) { piece_ = piece; }

std::string Spot::cvtPositionToName(Position pos) {
    std::array<std::string, 8> letters {"a", "b", "c", "d", "e", "f", "g", "h"};
    return letters[pos.x] + std::to_string(pos.y); // to resolve: [pos.x]
}

std::ostream& operator<<(std::ostream& os, const Spot& s) {
    if (s.piece_) s.piece_->print(os);
    else os << "_";
    return os;
}


