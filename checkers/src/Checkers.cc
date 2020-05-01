/**
 * @file Checkers.cc
 * @brief Source file for Checkers class, handling game mechanics.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include "Checkers.h"

Checkers::Checkers() : userPlayer_(true), compPlayer_(false) {}

std::string Checkers::findTile(std::string id){
	std::string result = id;
	result = "funkcja testowa";

	return result;
}

void Checkers::initialize(std::string userName, bool isUserWhite) {
	isUserWhite_ = isUserWhite;
	userName_ = userName;
}

bool Checkers::getIsUserWhite() { return isUserWhite_; }

std::string Checkers::getUserName() { return userName_;	}

