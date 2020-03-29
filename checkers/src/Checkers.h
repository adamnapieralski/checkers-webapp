/**
 * @file Checkers.h
 * 
 * @brief Class managing whole checkers game.
 */

#ifndef Checkers_h
#define Checkers_h

#include <iostream>

#include "Player.h"
#include "Board.h"

class Checkers {
private:
	Player userPlayer, compPlayer;
	Board board;

public:
	std::string findTile(std::string id); // temp test method 
};

#endif
