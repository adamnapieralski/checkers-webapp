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
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    std::array<std::array<PieceName,8>,8> getBoard();
    void placePiece(Position pos, PieceName piece);
    void movePiece(Position posStart, Position posEnd); 
    void makeMove(Move & move);

    std::string getFEN();


private:
    std::array<std::array<PieceName,8>,8> board_ ;
};

class Piece;

#endif  // BOARD_HPP