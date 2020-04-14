#include "Move.hpp"

Move::Move(Position s, Position e) : startPos(s), endPos(e) {}

Move::Move(Position s, Position e, Position c) : startPos(s), endPos(e) {
    capturedPos.push_back(c);
}

