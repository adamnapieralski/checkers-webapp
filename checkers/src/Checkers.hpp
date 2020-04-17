/**
 * @file Checkers.hpp
 * 
 * @brief Class managing whole checkers game.
 */

#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <iostream>
#include <string>

#include "Player.hpp"
#include "Board.hpp"

struct GameState {
	std::string boardFEN;
	bool isUserTurn;
	int uAP=12, uAK=0, uBP=0, uBK=0; // user's/copmuter's Alive/Beaten Pawns/Kings
	int cAP=12, cAK=0, cBP=0, cBK=0;
};

class Checkers {
public:
	// Checkers();
	// Checkers(bool isUserWhite);
	
	std::string findTile(std::string id); // temp test method

	void initialize(std::string userName, bool isUserWhite);
	bool getIsUserWhite();
	std::string getUserName();

	GameState processUserMove(std::string org, std::string dest) {	return GameState();	}
	GameState processComputerMove() {	return GameState();	}

private:
	//Player userPlayer_, compPlayer_;
	Board board_;
	bool isUserWhite_;
	std::string userName_;
};

#endif	// CHECKERS_HPP
