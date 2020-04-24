/**
 * Projekt Zaawansowane Programowanie w C++ - Warcaby
 * 24.04.2020
 * 
 * Autorzy: Patrycja Cieplicka, Adam Napieralski
 * 
 * Plik źródłowy klasy Checkers, która reprezentuje mechanikę gry (główna klasa)
 * 
 * */

#include "Checkers.hpp"

// Checkers::Checkers(bool isUserWhite) {
// 	//userPlayer_.setIsWhite(isUserWhite);

// 	//compPlayer_.setIsWhite(!isUserWhite);

// }

std::string Checkers::findTile(std::string id){
	std::string result = id;
	result = "e5";

	return result;
}

void Checkers::initialize(std::string userName, bool isUserWhite) {
	isUserWhite_ = isUserWhite;
	userName_ = userName;
}

bool Checkers::getIsUserWhite() { return isUserWhite_; }

std::string Checkers::getUserName() { return userName_;	}

