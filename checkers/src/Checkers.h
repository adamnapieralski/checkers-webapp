/**
 * @file Checkers.h
 * @brief Header file for Checkers class, handling game mechanics.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <string>

#include "UserPlayer.h"
#include "AIPlayer.h"
#include "Board.h"

struct GameState {
	std::string boardFEN;
	bool isUserTurn;
	int uAP=12, uAK=0, uBP=0, uBK=0; // user's/copmuter's Alive/Beaten Pawns/Kings
	int cAP=12, cAK=0, cBP=0, cBK=0;
};

class Checkers {
public:
	Checkers();
	
	std::string findTile(std::string id); // temporary test method

	void initialize(std::string userName, bool isUserWhite);
	bool getIsUserWhite();
	std::string getUserName();

	GameState processUserMove(std::string org, std::string dest) {	return GameState();	}
	GameState processComputerMove() {	return GameState();	}

private:
	UserPlayer userPlayer_;
	AIPlayer compPlayer_;
	Board board_;
	bool isUserWhite_;
	std::string userName_;
};

#endif	// CHECKERS_H
