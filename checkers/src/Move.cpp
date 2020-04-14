#include "Move.hpp"

Move::Move(Position s, Position e) : startPos(s), endPos(e) {}

Move::Move(Position s, Position e, Position c) : startPos(s), endPos(e) {
    capturedPos.push_back(c);
}

void Move::addStepMove(Move tmp){
    if(!startPos.x){
        startPos = tmp.startPos;
    }
    endPos = tmp.endPos;
    stepMoves.push_back(tmp);
    capturedPos.push_back(tmp.capturedPos[0]);
}

bool Move::operator==(const Move& move) const{
        if (move.startPos == startPos && move.endPos == endPos && move.stepMoves == stepMoves ) return true;
        return false;
    }