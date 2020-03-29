#ifndef Board_h
#define Board_h

#include <array>

#include "Spot.h"

class Board {
private:
    std::array<std::array<Spot, 8>, 8> spots;

public:
    void initialize();

    std::string getFEN();
};

#endif