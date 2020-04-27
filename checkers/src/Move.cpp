/**
 * @file Move.cpp
 * @brief Source file for Move class, representing move of pieces.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "Move.hpp"

Move::Move(Position s, Position e) : startPos_(s), endPos_(e) {}

Move::Move(Position s, Position e, Position c) : startPos_(s), endPos_(e) {
    capturedPos_.push_back(c);
}

/*void Move::addStepMove(Move tmp){
    if(!startPos_.x){
        startPos_ = tmp.startPos_;
    }
    endPos_ = tmp.endPos_;
    stepMoves_.push_back(tmp);
    capturedPos_.push_back(tmp.capturedPos_[0]);
}*/

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
    if(!changePos_.empty()){
        merged.changePos_ = changePos_;
    }
    return merged;
}

void Move::addChange(Position pos){
    changePos_.push_back(pos);
}

std::vector<Position> Move::getChangedPosition() const { return changePos_ ; }

Position Move::getStartPosition() const { return startPos_;   }

Position Move::getEndPosition() const { return endPos_; }

std::vector<Position> Move::getCapturedPositions() const {  return capturedPos_;    }

std::vector<Move> Move::getStepMoves() const { return stepMoves_;  }