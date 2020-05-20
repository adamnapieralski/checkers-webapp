/**
 * @file Move.cc
 * @brief Source file for Move class, representing move of pieces.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "Move.h"
#include <algorithm>

Move::Move(Position s, Position e) : startPos_(s), endPos_(e) {}

Move::Move(Position s, Position e, Position c) : startPos_(s), endPos_(e) {
    capturedPos_.push_back(c);
}

bool Move::isInitial() const {
    Move initial;
    if (*this == initial) return true;
    else return false;
}

bool Move::operator==(const Move& move) const {
    if (move.startPos_ == startPos_ && move.endPos_ == endPos_ &&
        move.stepMoves_ == stepMoves_ && move.capturedPos_ == capturedPos_) return true;
    return false;
}


Move Move::merge(Move& next) const {
    if (endPos_ != next.startPos_)
        throw std::out_of_range("Start and end positions of moves to merge do not match.");

    Move merged(startPos_, next.endPos_);

    for (auto& mv : std::vector<Move>{*this, next}) {
        if (mv.stepMoves_.empty()) {
            merged.stepMoves_.push_back(mv);
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
    if(!upgradePos_.empty()) {
        merged.upgradePos_= upgradePos_;
    }
    return merged;
}

void Move::addUpgradePosition(const Position& pos){
    upgradePos_.push_back(pos);
}

void Move::addCapturedPosition(const Position& pos) {
    capturedPos_.push_back(pos);
}


std::vector<Position> Move::getUpgradePositions() const { return upgradePos_ ; }

Position Move::getStartPosition() const { return startPos_;   }

Position Move::getEndPosition() const { return endPos_; }

std::vector<Position> Move::getCapturedPositions() const {  return capturedPos_;    }

std::vector<Move> Move::getStepMoves() const { return stepMoves_;  }

bool Move::containsAsStep(const Move& move) const {
    auto it = std::find(stepMoves_.begin(), stepMoves_.end(), move);
    if (it != stepMoves_.end()) {
        return true;
    }
    return false;
}
