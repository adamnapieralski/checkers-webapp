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
	bool hasGameEnded;
	bool hasUserWon;
};

class Checkers {
public:
	static Checkers& getInstance();
	
	void initialize(std::string userName, bool isUserWhite);
	bool getIsUserWhite();
	std::string getUserName();
	bool checkIfEndGame();

	GameState getGameState() const;

	void updateState(bool hasMoreMoves=false);

	// GameState processUserMove(GameState state);
	GameState processUserMove(std::string origin, std::string destination);
	//GameState processUserMove(std::string org, std::string dest);
	Board getBoard() const;

private:
	Checkers();
	// Checkers(const Checkers&) = delete;
	// Checkers& operator=(const Checkers&) = delete;

	UserPlayer userPlayer_;
	AIPlayer compPlayer_;
	Board board_;
	GameState state_;
};

#endif	// CHECKERS_H
