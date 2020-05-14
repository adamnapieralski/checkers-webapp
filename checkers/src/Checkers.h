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
	bool endPlay;
	bool ifUserWin;
};

class Checkers {
public:
	static Checkers& getInstance();
	
	std::string findTile(std::string id); // temporary test method

	void initialize(std::string userName, bool isUserWhite);
	bool getIsUserWhite();
	std::string getUserName();
	bool checkIfEndGame();

	GameState processUserMove(GameState state);
	//GameState processUserMove(std::string org, std::string dest);

private:
	Checkers();
	Checkers(const Checkers&) = delete;
	Checkers& operator=(const Checkers&) = delete;

	UserPlayer userPlayer_;
	AIPlayer compPlayer_;
	Board board_;
	GameState state_;
};

#endif	// CHECKERS_H
