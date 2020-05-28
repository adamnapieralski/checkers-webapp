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

enum Score {
	IN_PROGRESS, USER_WON, USER_LOST, DRAW
};

struct GameState {
	std::string userName;
	bool isUserWhite;
	std::string boardFEN;
	bool isUserTurn;
	int uAP=12, uAK=0, uBP=0, uBK=0; // user's/copmuter's Alive/Beaten Pawns/Kings
	int cAP=12, cAK=0, cBP=0, cBK=0;
	bool hasGameEnded;
	bool hasUserWon;
	Move lastMove;
	bool isInMultipleMove;
	int nonCaptureSequence;
	Score score;
};

class Checkers {
public:
	static Checkers& getInstance();
	
	void initialize(std::string userName, bool isUserWhite);
	void fenInitialize(std::string fen, std::string userName, bool isUserWhite, bool isUserTurn);
	bool getIsUserWhite();
	std::string getUserName();
	bool checkIfEndGame();

	GameState getGameState() const;

	void updateState(const Move& lastMove, bool hasMoreMoves=false);
	void updateScore();

	// GameState processUserMove(GameState state);
	GameState processUserMove(std::string origin, std::string destination);
	GameState makeComputerMove();
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
