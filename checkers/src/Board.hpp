#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <iostream>

#include "Spot.hpp"
#include "Player.hpp"


class Board {
public:
    Board();
    void initialize(Player &user, Player &computer);

    bool isMoveValid(Position origin, Position dest);

    friend std::ostream& operator<<(std::ostream& os, const Board& b);

    Spot& getSpotOnPosition(Position pos);

    // std::string getFEN();

private:
    int sizeX_ = 8;
    int sizeY_ = 8;
    std::vector<std::vector<Spot>> spots_;
};

class Piece;

#endif  // BOARD_HPP