#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <iostream>

#include "Position.hpp"
#include "Move.hpp"


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

private:
    std::array<std::array<PieceName,8>,8> board_ ;
};

class Piece;

#endif  // BOARD_HPP