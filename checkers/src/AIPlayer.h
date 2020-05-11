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
#include "GameTree.h"

class AIPlayer : public Player {
public:
    AIPlayer(bool isWhite);

    void initializePieces(Board &board) override;
    void addPiece(bool isKing, Position pos, Board &board) override; 

    // GameTree getGameTree(const UserPlayer &user, const Board &board);
    // void fillTree(AIPlayer computer, UserPlayer user, GameTree &tree, int depth, Board board, bool ifUser);
    Move minmax(AIPlayer computer, UserPlayer user, Board board);

private:
    double minmaxAlphaBeta(AIPlayer computer, UserPlayer user, Board board, int depth, double alpha, double beta, bool ifUser);
    double evaluationFunction(AIPlayer computer, UserPlayer user, Board board);
};

#endif  // AIPLAYER_H