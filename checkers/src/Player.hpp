/**
 * @file Player.hpp
 * @brief Header file for Player class, representing player.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>
#include "Piece.hpp"
#include "Board.hpp"

class Player {
public:

    Player(bool isWhite, bool isUser);
    Player(){};

    bool isWhite() const;
    void setHasTurn(bool hasTurn) const;

    void initializePieces(Board &board);
    void movePiece(Board &board, Player &opponent, Move move);
    void erasePiece(std::shared_ptr<Piece> piece);
    void changePiece(std::shared_ptr<Piece> piece, Position pos);
    void addPiece(bool isKing, Position pos, Board &board); 
    std::vector<std::vector<Move>> getValidMoves(Board &board) const;
    std::vector<std::shared_ptr<Piece>> getPieces() const; 
    std::shared_ptr<Piece> findPiece(Position &pos) const;

        //void printPlayer(); // testy
    

private:
    std::vector<std::shared_ptr<Piece>> pieces_;
    bool hasTurn_;
    bool isWhite_;
    bool isUser_;
};

#endif  // PLAYER_HPP