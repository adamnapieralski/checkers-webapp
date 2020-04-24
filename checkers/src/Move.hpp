#ifndef MOVE_HPP
#define MOVE_HPP

#include <vector>

#include "Position.hpp"

class Move {
public:
    Move(){};
    Move(Position, Position);
    Move(Position, Position, Position);

    //void addStepMove(Move tmp);
    void addChange(Position pos);
    bool isInitial() const;
    Move merge(Move& next) const;

    Position getStartPosition() const;
    Position getEndPosition() const;
    std::vector<Position> getChangedPosition() const;
    std::vector<Position> getCapturedPositions() const;
    std::vector<Move> getStepMoves() const;

    bool operator==(const Move& move) const;

private:
    Position startPos_, endPos_;
    std::vector<Position> capturedPos_;
    std::vector<Move> stepMoves_;
    std::vector<Position> changePos_;

};

#endif  // MOVE_HPP