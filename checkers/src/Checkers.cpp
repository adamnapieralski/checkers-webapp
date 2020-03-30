#include "Checkers.hpp"

Checkers::Checkers(bool isUserWhite) {
	userPlayer_.setIsWhite(isUserWhite);
	userPlayer_.setHasTurn(isUserWhite);

	compPlayer_.setIsWhite(!isUserWhite);
	compPlayer_.setHasTurn(!isUserWhite);

	board_.initialize(userPlayer_, compPlayer_);
}

std::string Checkers::findTile(std::string id){
	std::string result = "e5";

	return result;
}
