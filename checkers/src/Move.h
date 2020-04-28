/**
 * @file Move.h
 * @brief Source file for Move class, representing move of pieces.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */


#ifndef MOVE_H
#define MOVE_H

#include <vector>

#include "Position.h"

class Move {
public:
    Move(){};
    Move(Position, Position);
    Move(Position, Position, Position);

    void addUpgradePosition(const Position& pos);
    bool isInitial() const;
    Move merge(Move& next) const;

    Position getStartPosition() const;
    Position getEndPosition() const;
    std::vector<Position> getUpgradePositions() const;
    std::vector<Position> getCapturedPositions() const;
    std::vector<Move> getStepMoves() const;

    bool operator==(const Move& move) const;

private:
    Position startPos_, endPos_;
    std::vector<Position> capturedPos_;
    std::vector<Move> stepMoves_;
    std::vector<Position> upgradePos_;

};

#endif  // MOVE_H