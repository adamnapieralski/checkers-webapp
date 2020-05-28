/**
 * @file Checkers.cc
 * @brief Source file for Checkers class, handling game mechanics.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include "Checkers.h"

Checkers& Checkers::getInstance() {
	static Checkers instance;
	return instance;
}

Checkers::Checkers() : userPlayer_(true), compPlayer_(false) {}

void Checkers::initialize(std::string userName, bool isUserWhite) {
	userPlayer_.setName(userName);
	userPlayer_.setIsWhite(isUserWhite);
	compPlayer_.setIsWhite(!isUserWhite);

	board_.clear();	
	userPlayer_.initializePieces(board_);
	compPlayer_.initializePieces(board_);

	state_.userName = userName;
	state_.isUserWhite = isUserWhite;
	state_.boardFEN = board_.getFEN();
	state_.isUserTurn = isUserWhite;
	state_.nonCaptureSequence = 0;
	state_.score = Score::IN_PROGRESS;
}

void Checkers::fenInitialize(std::string fen, std::string userName, bool isUserWhite, bool isUserTurn) {
	board_ = Board(fen);

	userPlayer_.setIsWhite(isUserWhite);
	compPlayer_.setIsWhite(!isUserWhite);

	userPlayer_.initializePiecesFromBoard(board_);
	compPlayer_.initializePiecesFromBoard(board_);

	state_.boardFEN = fen;
	state_.isUserTurn = isUserTurn;

}


void Checkers::updateState(const Move& lastMove, bool hasMoreMoves) {
	state_.boardFEN = board_.getFEN();
	state_.uAP = userPlayer_.getNumberOfPawns(board_);
	state_.cAP = compPlayer_.getNumberOfPawns(board_);
	state_.uAK = userPlayer_.getNumberOfKings(board_);
	state_.cAK = compPlayer_.getNumberOfKings(board_);
	state_.lastMove = lastMove;
	state_.hasGameEnded = checkIfEndGame();
	state_.isInMultipleMove = hasMoreMoves;

	if (lastMove.getCapturedPositions().empty()) {
		++state_.nonCaptureSequence;
	}
	else {
		state_.nonCaptureSequence = 0;
	}

	if (!hasMoreMoves) {
		state_.isUserTurn = !state_.isUserTurn;
	}
	updateScore();
}

GameState Checkers::getGameState() const {
	return state_;
}

Board Checkers::getBoard() const {
	return board_;
}

GameState Checkers::processUserMove(std::string origin, std::string destination) {
	try {
		if (!state_.isUserTurn) {
			return state_;
		}
		Position org = board_.getPositionByName(origin);
		Position dest = board_.getPositionByName(destination);
		Move triedMove = board_.findUserMove(org, dest);
		if (userPlayer_.isMoveValid(triedMove, board_)) {
			if (state_.isInMultipleMove) {
				if (triedMove.getStartPosition() != state_.lastMove.getEndPosition()) {
					return state_;
				}
			}
			bool isMoveMultiple = userPlayer_.isMoveMultiple(triedMove, board_);
			userPlayer_.movePiece(board_, compPlayer_, triedMove);
			updateState(triedMove, isMoveMultiple);
		}
		return state_;
	}
	catch (std::out_of_range& e) {
		return state_;
	}
}
GameState Checkers::makeComputerMove() {
	if (state_.isUserTurn) {
		return state_;
	}

	auto move = compPlayer_.makeMinmaxMove(userPlayer_, board_);
	updateState(move);
	return state_;
}

bool Checkers::getIsUserWhite() { return userPlayer_.isWhite(); }

std::string Checkers::getUserName() { return userPlayer_.getName(); }

bool Checkers::checkIfEndGame(){
	if(userPlayer_.getPieces().size() == 0) {
		state_.hasUserWon = false;
		return true;
	}

	else if(compPlayer_.getPieces().size() == 0) {
		state_.hasUserWon = true;
		return true;
	}

	else if(state_.isUserTurn){
		std::vector<std::vector<Move>> moves = userPlayer_.getValidMoves(board_);
		if(moves.empty()){
			state_.hasUserWon = false;
			return true;
		}
	}

	else if(!state_.isUserTurn){
		std::vector<std::vector<Move>> moves = compPlayer_.getValidMoves(board_);
		if(moves.empty()){
			state_.hasUserWon = true;
			return true;
		}
	}
	
	return false;
}

void Checkers::updateScore() {
	// both users made 15 moves with no capture
	if (state_.nonCaptureSequence == 30) {
		state_.score = Score::DRAW;
	}
	else if(userPlayer_.getPieces().empty()) {
		state_.score = Score::USER_LOST;
	}
	else if(compPlayer_.getPieces().empty()) {
		state_.score = Score::USER_WON;
	}
	else if(state_.isUserTurn && userPlayer_.getValidMoves(board_).empty()){
		state_.score = Score::USER_LOST;
	}

	else if(!state_.isUserTurn && compPlayer_.getValidMoves(board_).empty()){
		state_.score = Score::USER_WON;
	}
}
