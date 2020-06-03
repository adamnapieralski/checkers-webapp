/**
 * @file Board.h
 * @brief Header file for Board class, representing checkers board.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <vector>
#include <iostream>

#include "Position.h"
#include "Move.h"

#define BOARD_SIZE 8

/**
 * Describes Pieces on Board
 * */
enum PieceName {
    EMPTY, WHITE_KING, WHITE_PAWN, BLACK_KING, BLACK_PAWN
};

/**
 * Class representing checkers board
 * */
class Board {
public:
    Board();
    Board(std::string fen);

    void clear();
    void clearPosition(const Position& pos);
    void placePiece(const Position& pos, PieceName piece);
    void movePiece(const Position& posStart, const Position& posEnd);
    void makeMove(const Move& m);

    Move findUserMove(const Position& origin, const Position& destination);

    std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> getBoard() const;
    PieceName getPieceName(const Position& pos) const;

    bool arePiecesSameColor(PieceName p1, PieceName p2);
    bool arePiecesDifferentColor(PieceName p1, PieceName p2);

    bool isPositionNameValid(std::string pos) const;
    Position getPositionByName(std::string pos) const;

    std::string getFEN() const;

    Board& operator=(Board other);

    friend void swap(Board& b1, Board& b2);
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    friend std::ostream& operator<<(std::ostream& os, const PieceName& p);

private:
    void initializePositionNames();

    std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> board_ ; // <! array representing board
    
    std::map<std::string, Position> positionNames_; // <! Map position names to easier representation

    std::string positionLetters_ = "abcdefgh";
    std::string positionNumbers_ = "12345678";

    const std::map<enum PieceName, char>  fenPiecesNames_ = {
        { EMPTY, 'e' }, { WHITE_PAWN , 'P' }, { WHITE_KING, 'K' }, { BLACK_PAWN, 'p' }, { BLACK_KING, 'k' }
    };
};

#endif  // BOARD_H