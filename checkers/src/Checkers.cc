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


std::string Checkers::findTile(std::string id){
	std::string result;
	if(id == "tak"){
		result = "funkcja testowa";
	}
	else result = id;

	return result;
}

void Checkers::initialize(std::string userName, bool isUserWhite) {
	userPlayer_.setName(userName);
	userPlayer_.setIsWhite(isUserWhite);
	compPlayer_.setIsWhite(!isUserWhite);
	
	userPlayer_.initializePieces(board_);
	compPlayer_.initializePieces(board_);

	state_.boardFEN = board_.getFEN();
}

GameState Checkers::processUserMove(GameState state){

	Board temp = Board(state.boardFEN);
	if(userPlayer_.checkIfValidMove(temp, board_)){
		//user robi ruch; moze chek valid move niech zwraca Move?
		state_.isUserTurn = false;
	}
	else{
		//wysylamy komunikat, ze nie prawidlowy ruch ?
		return state_;
	}

	if(!checkIfEndGame()){
		compPlayer_.makeMove(userPlayer_ , board_);
	}
	else{
		state_.endPlay = true;
		return state_;
	}

	state_.isUserTurn = true;
	state_.boardFEN = board_.getFEN();
	state_.uAP = userPlayer_.getNumberOfPawns(board_);
	state_.cAP = compPlayer_.getNumberOfPawns(board_);
	state_.uAK = userPlayer_.getNumberOfKings(board_);
	state_.cAK = compPlayer_.getNumberOfKings(board_);

	if(checkIfEndGame()){
		state_.endPlay = true;
	}

	return state_;
}

/*GameState Checkers::processUserMove(std::string org, std::string dest){
	return state_;
}*/

bool Checkers::getIsUserWhite() { return userPlayer_.isWhite(); }

std::string Checkers::getUserName() { return userPlayer_.getName(); }

bool Checkers::checkIfEndGame(){
	if(userPlayer_.getPieces().size() == 0) {
		state_.ifUserWin = false;
		return true;
	}

	else if(compPlayer_.getPieces().size() == 0) {
		state_.ifUserWin = true;
		return true;
	}

	else if(state_.isUserTurn){
		std::vector<std::vector<Move>> moves = userPlayer_.getValidMoves(board_);
		if(moves.empty()){
			state_.ifUserWin = false;
			return true;
		}
	}

	else if(!state_.isUserTurn){
		std::vector<std::vector<Move>> moves = compPlayer_.getValidMoves(board_);
		if(moves.empty()){
			state_.ifUserWin = true;
			return true;
		}
	}
	
	else return false;
}

