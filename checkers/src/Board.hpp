/**
 * @file Board.hpp
 * @brief Header file for Board class, representing checkers board.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <iostream>

#include "Position.hpp"
#include "Move.hpp"

#define BOARD_SIZE 8

enum PieceName {
    EMPTY, WHITE_KING, WHITE_PAWN, BLACK_KING, BLACK_PAWN
};

class Board {
public:
    Board();
    std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> getBoard();
    void clearPosition(Position pos);
    void placePiece(Position pos, PieceName piece);
    void movePiece(Position posStart, Position posEnd);
    PieceName getPieceName(Position pos);
    void makeMove(const Move& m);

    /**
     * Get string describing current board state with 1. field of FEN record
     * https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
     */
    std::string getFEN();

    Board& operator=(Board other);

    friend void swap(Board& b1, Board& b2);
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    friend std::ostream& operator<<(std::ostream& os, const PieceName& p);

private:
    std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> board_ ;
};

#endif  // BOARD_HPP