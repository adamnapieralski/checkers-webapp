#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <iostream>

#include "Position.hpp"


class Board {
public:
    Board();
    friend std::ostream& operator<<(std::ostream& os, const Board& b);


private:
    std::array<std::array<PieceName,8>,8> board_ ;
    int sizeX_ = 8;
    int sizeY_ = 8;
};

class Piece;

#endif  // BOARD_HPP