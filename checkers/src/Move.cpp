#include "Move.hpp"

Move::Move(Position s, Position e) : startPos(s), endPos(e) {}

Move::Move(Position s, Position e, Position c) : startPos(s), endPos(e) {
    capturedPos.push_back(c);
}

Move Move::merge(Move& next) {
    if (endPos != next.startPos)
        throw std::out_of_range("");

    Move merged(startPos, next.endPos);

    for (auto& mv : std::vector<Move>{*this, next}) {
        if (mv.stepMoves.empty()) {
            merged.stepMoves.push_back(*this);
        }
        else {
            for (auto& m : mv.stepMoves) {
                merged.stepMoves.push_back(m);
            }
        }
        for (auto& c : mv.capturedPos) {
            merged.capturedPos.push_back(c);
        }
    }
    return merged;
}

