#ifndef MOVE_HPP
#define MOVE_HPP

#include <vector>

#include "Position.hpp"

class Move {
public:
    Move(Position s, Position e);
    Move(Position s, Position e, Position c);

    Move merge(Move& next);

private:
    Position startPos, endPos;
    std::vector<Position> capturedPos;
    std::vector<Move> stepMoves;
};

#endif  // MOVE_HPP