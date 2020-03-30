#ifndef Board_h
#define Board_h

#include <array>
#include <vector>

#include "Spot.h"
#include "Player.h"

class Board {
public:
    Board();
    void initialize(Player &user, Player &computer);

    // std::string getFEN();

private:
    int sizeX_ = 8;
    int sizeY_ = 8;
    std::vector<std::vector<Spot>> spots_;
};

#endif