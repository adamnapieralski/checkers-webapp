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

/**
 * Describes the game status
 * */
enum Score {
	IN_PROGRESS, USER_WON, USER_LOST, DRAW
};

/**
 * Struct representing Game State
 * @param uAP user's alive Pawns
 * @param uAK user's alive King
 * @param cAP computer's alive Pawns
 * @param cAK computer's alive Kings
 * @param boardFEN string describing current board state
 * */
struct GameState {
	std::string userName;
	bool isUserWhite;
	std::string boardFEN;
	bool isUserTurn;
	int uAP=12, uAK=0;
	int cAP=12, cAK=0;
	bool hasGameEnded;
	Move lastMove;
	bool isInMultipleMove;
	int nonCaptureSequence;
	Score score;
};

/**
 * Class handling game mechanics
 * */
class Checkers {
public:
	static Checkers& getInstance();
	
	void initialize(std::string userName, bool isUserWhite);
	void fenInitialize(std::string fen, std::string userName, bool isUserWhite, bool isUserTurn);

	GameState getGameState() const;

	void updateState(const Move& lastMove, bool hasMoreMoves=false);
	void updateScore();

	//Functions making moves on board
	GameState processUserMove(std::string origin, std::string destination);
	GameState makeComputerMove();

	Board getBoard() const;

private:
	Checkers();

	UserPlayer userPlayer_;
	AIPlayer compPlayer_;
	Board board_;
	GameState state_;
};

#endif	// CHECKERS_H
