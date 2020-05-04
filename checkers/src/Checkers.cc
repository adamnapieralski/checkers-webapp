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
	std::string result = id;
	result = "funkcja testowa";

	return result;
}

void Checkers::initialize(std::string userName, bool isUserWhite) {
	userPlayer_.setName(userName);
	userPlayer_.setIsWhite(isUserWhite);
	compPlayer_.setIsWhite(!isUserWhite);
	
	userPlayer_.initializePieces(board_);
	compPlayer_.initializePieces(board_);
}

bool Checkers::getIsUserWhite() { return userPlayer_.isWhite(); }

std::string Checkers::getUserName() { return userPlayer_.getName(); }

