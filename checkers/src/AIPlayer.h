/**
 * @file AIPlayer.h
 * @brief Header file for AIPlayer class, representing AI player.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include "UserPlayer.h"

class AIPlayer : public Player {
public:
    AIPlayer(bool isWhite);

    void initializePieces(Board &board) override;
    void addPiece(bool isKing, Position pos, Board &board) override; 

    GameTree getGameTree(UserPlayer user, Board &board);
    Move minmax();

private:
    double minmaxAlphaBeta();
};

#endif  // AIPLAYER_H