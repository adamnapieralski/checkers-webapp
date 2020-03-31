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

    friend std::ostream& operator<<(std::ostream& os, const Board& b);

    // std::string getFEN();

private:
    int sizeX_ = 8;
    int sizeY_ = 8;
    std::vector<std::vector<Spot>> spots_;
};

#endif  // BOARD_HPP