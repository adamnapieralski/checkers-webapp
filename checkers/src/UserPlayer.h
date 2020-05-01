/**
 * @file UserPlayer.h
 * @brief Header file for UserPlayer class, representing AI player.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#ifndef USERPLAYER_H
#define USERPLAYER_H

#include "Player.h"

class UserPlayer : public Player {
public:
    UserPlayer(bool isWhite);

    void initializePieces(Board &board) override;
    void addPiece(bool isKing, Position pos, Board &board) override; 

};

#endif  // USERPLAYER_H