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
public:
	Checkers(bool isUserWhite);
	std::string findTile(std::string id); // temp test method

private:
	Player userPlayer_, compPlayer_;
	Board board_;
};

#endif
