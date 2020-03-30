/**
 * @file Checkers.hpp
 * 
 * @brief Class managing whole checkers game.
 */

#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <iostream>

#include "Player.hpp"
#include "Board.hpp"

class Checkers {
public:
	Checkers(bool isUserWhite);
	std::string findTile(std::string id); // temp test method

private:
	Player userPlayer_, compPlayer_;
	Board board_;
};

#endif	// CHECKERS_HPP
