/**
 * @file UserPlayer.cc
 * @brief Source file for UserPlayer class, representing user player.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "UserPlayer.h"
#include "Pawn.h"
#include "King.h"

UserPlayer::UserPlayer(bool isWhite) : Player(isWhite) {}

UserPlayer::UserPlayer(bool isWhite, std::string name) : Player(isWhite) {
    name_ = name;
}

void UserPlayer::initializePieces(Board& board){
    for (int i = 0; i < INIT_ROW; ++i){
        for(int j = 0; j < BOARD_SIZE; ++j) {
            if ((i + j) % 2 == 0) {
                pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, true, board));
            }
        }
    }
}

void UserPlayer::addPiece(bool isKing, Position pos, Board& board) {
    if(isKing) pieces_.push_back(std::make_shared<King>(pos, isWhite_, true, board));
    else pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, true, board));
}