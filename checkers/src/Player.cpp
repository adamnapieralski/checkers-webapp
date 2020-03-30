#include "Player.hpp"

bool Player::isWhite() {    return isWhite_;    }

void Player::setIsWhite(bool isWhite) { isWhite_ = isWhite; }

void Player::addPiece(Piece* piece) {   pieces_.push_back(piece);   }

void Player::setHasTurn(bool hasTurn) { hasTurn_ = hasTurn; }