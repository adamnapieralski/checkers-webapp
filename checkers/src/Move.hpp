#ifndef MOVE_HPP
#define MOVE_HPP

#include <vector>

#include "Position.hpp"

class Move {
public:
    Move(Position s, Position e);
    Move(Position s, Position e, Position c);

    Move merge(Move& next);

    Position getStartPosition() const;
    Position getEndPosition() const;
    std::vector<Position> getCapturedPositions() const;
    std::vector<Move> getStepMoves() const;

private:
    Position startPos_, endPos_;
    std::vector<Position> capturedPos_;
    std::vector<Move> stepMoves_;
};

#endif  // MOVE_HPP