#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <iostream>

#include "Position.hpp"
#include "Move.hpp"

enum PieceName {
    EMPTY, WHITE_KING, WHITE_PAWN, BLACK_KING, BLACK_PAWN
};

class Board {
public:
    Board();
    std::array<std::array<PieceName,8>,8> getBoard();
    void clearPosition(Position pos);
    void placePiece(Position pos, PieceName piece);
    void movePiece(Position posStart, Position posEnd);
    PieceName getPieceName(Position pos);
    void makeMove(const Move& m);

    std::string getFEN();

    Board& operator=(Board other);

    friend void swap(Board& b1, Board& b2);
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    friend std::ostream& operator<<(std::ostream& os, const PieceName& p);

private:
    std::array<std::array<PieceName,8>,8> board_ ;
};

#endif  // BOARD_HPP