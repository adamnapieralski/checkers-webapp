#include "Move.hpp"

Move::Move(Position s, Position e) : startPos_(s), endPos_(e) {}

Move::Move(Position s, Position e, Position c) : startPos_(s), endPos_(e) {
    capturedPos_.push_back(c);
}

Move Move::merge(Move& next) {
    if (endPos_ != next.startPos_)
        throw std::out_of_range("");

    Move merged(startPos_, next.endPos_);

    for (auto& mv : std::vector<Move>{*this, next}) {
        if (mv.stepMoves_.empty()) {
            merged.stepMoves_.push_back(*this);
        }
        else {
            for (auto& m : mv.stepMoves_) {
                merged.stepMoves_.push_back(m);
            }
        }
        for (auto& c : mv.capturedPos_) {
            merged.capturedPos_.push_back(c);
        }
    }
    return merged;
}

Position Move::getStartPosition() const { return startPos_;   }

Position Move::getEndPosition() const { return endPos_; }

std::vector<Position> Move::getCapturedPositions() const {  return capturedPos_;    }

std::vector<Move> Move::getStepMoves() const { return stepMoves_;  }

