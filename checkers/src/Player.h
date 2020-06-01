/**
 * @file Player.h
 * @brief Header file for Player class, representing player.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include "Piece.h"
#include "Board.h"

/**
 * Class representing Player
 * */
class Player {
public:

    Player(bool isWhite);
    Player(){};

    Player(const Player& p);
    Player& operator=(const Player& p);
    
    virtual ~Player(){};

    bool isWhite() const;
    std::string getName() const;

    void setIsWhite(bool isWhite);
    void setName(std::string name);

    void setHasTurn(bool hasTurn);
    int getNumberOfPawns(Board& board);
    int getNumberOfKings(Board& board);

    // functions connected with movment of pieces at board
    
    /**
     * Initialize Pieces on Board and add owned Pieces for new Game
     * */
    virtual void initializePieces(Board &board) = 0;
    virtual void initializePiecesFromBoard(Board& board) = 0;
    virtual void addPiece(bool isKing, Position pos, Board &board) = 0; 
    void movePiece(Board& board, Player& opponent, const Move& move);
    void erasePiece(std::shared_ptr<Piece> piece);
    void changePiece(std::shared_ptr<Piece> piece, const Position& pos);

    /**
     * Get all valid moves for owned pieces on board, respecting the rule of capture obligation.
     */
    std::vector<std::vector<Move>> getValidMoves(Board& board) const;
    std::vector<std::shared_ptr<Piece>> getPieces() const; 
    std::shared_ptr<Piece> findPiece(const Position& pos) const;

    bool canCapture(Board& board) const;
    bool isMoveValid(const Move& move, Board& board) const;
    bool isMoveMultiple(const Move& move, Board& board) const;

protected:
    void initializePiecesFromBoardPerUser(Board& board, bool isUser);

    const int INIT_ROW = 3;

    std::vector<std::shared_ptr<Piece>> pieces_;
    bool hasTurn_;
    bool isWhite_;
    std::string name_;

};

#endif  // PLAYER_H