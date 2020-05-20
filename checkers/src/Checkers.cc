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
	
	userPlayer_.initializePieces(board_);
	compPlayer_.initializePieces(board_);

	state_.boardFEN = board_.getFEN();
	state_.isUserTurn = isUserWhite;
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
	if (!hasMoreMoves) {
		state_.isUserTurn = !state_.isUserTurn;
	}
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
			auto isMoveMultiple = userPlayer_.isMoveMultiple(triedMove, board_);
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


// GameState Checkers::processUserMove(GameState state) {

// 	Board temp = Board(state.boardFEN);
// 	if(userPlayer_.checkIfValidMove(temp, board_)){
// 		//user robi ruch; moze chek valid move niech zwraca Move?
// 		state_.isUserTurn = false;
// 	}
// 	else{
// 		//wysylamy komunikat, ze nie prawidlowy ruch ?
// 		return state_;
// 	}

// 	if(!checkIfEndGame()){
// 		compPlayer_.makeMove(userPlayer_ , board_);
// 	}
// 	else{
// 		state_.endPlay = true;
// 		return state_;
// 	}

// 	state_.isUserTurn = true;
// 	state_.boardFEN = board_.getFEN();
// 	state_.uAP = userPlayer_.getNumberOfPawns(board_);
// 	state_.cAP = compPlayer_.getNumberOfPawns(board_);
// 	state_.uAK = userPlayer_.getNumberOfKings(board_);
// 	state_.cAK = compPlayer_.getNumberOfKings(board_);

// 	if(checkIfEndGame()){
// 		state_.endPlay = true;
// 	}

// 	return state_;
// }

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

