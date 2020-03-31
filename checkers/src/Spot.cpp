#include "Spot.hpp"

Spot::Spot(int x, int y) {
    if (isPositionValid(x, y)) {
        x_ = x;
        y_ = y;
        isDark_ = (x + y + 1) % 2;
        name_ = cvtPositionToName(x, y);
        piece_ = nullptr;
    }

}

int Spot::getX() {  return x_;  }

int Spot::getY() {  return y_;  }

bool Spot::isPositionValid(int x, int y) {
    if (x >= 0 && x <= 8 && y >=0 && y <=8) return true;
    else return false;
}

bool Spot::isDark() { return isDark_; }

bool Spot::isFree() {
    if (piece_ == nullptr) return true;
    else return false;
}

void Spot::setPiece(Piece *piece) { piece_ = piece; }

std::string Spot::cvtPositionToName(int x, int y) {
    std::array<std::string, 8> letters {"a", "b", "c", "d", "e", "f", "g", "h"};
    return letters[x] + std::to_string(y);
}

std::ostream& operator<<(std::ostream& os, const Spot& s) {
    if (s.piece_) s.piece_->print(os);
    else os << "_";
    return os;
}


