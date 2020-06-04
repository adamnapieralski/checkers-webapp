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

/**
 * Class representing AI Player
 * */
class AIPlayer : public Player {
public:
    AIPlayer(bool isWhite);

    void initializePieces(Board &board) override;
    void initializePiecesFromBoard(Board& board) override;
    void addPiece(bool isKing, Position pos, Board &board) override; 

    Move minmax(AIPlayer computer, UserPlayer user, Board board);
    Move makeMinmaxMove(UserPlayer& user, Board& board);

private:
    double minmaxAlphaBeta(AIPlayer computer, UserPlayer user, Board board, int depth, double alpha, double beta, bool ifUser);
    double evaluationFunction(AIPlayer computer, UserPlayer user, Board board);
};

#endif  // AIPLAYER_H