/**
 * @file AIPlayer.cc
 * @brief Source file for AI class, representing AI player.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "AIPlayer.h"
#include "Pawn.h"
#include "King.h"
#include "GameTree.h"

AIPlayer::AIPlayer(bool isWhite) : Player(isWhite) {
    name_ = "Computer";
}

void AIPlayer::initializePieces(Board& board){
    for (int i = BOARD_SIZE - 1; i > INIT_ROW + 1; --i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            if ((i + j) % 2 == 0){
                pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, false, board));
            }
        }
    }
}

void AIPlayer::addPiece(bool isKing, Position pos, Board& board){
    if(isKing) pieces_.push_back(std::make_shared<King>(pos, isWhite_, false, board));
    else pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, false, board));
}

Move AIPlayer::minmax() {
    return Move();
}

double AIPlayer::minmaxAlphaBeta() {
    return 0.;
}

GameTree AIPlayer::getGameTree(UserPlayer user, Board &board){
    this->getValidMoves(board);

}