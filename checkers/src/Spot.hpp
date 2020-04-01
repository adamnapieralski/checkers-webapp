#ifndef SPOT_HPP
#define SPOT_HPP

#include <string>
#include <array>
#include <iostream>

#include "Piece.hpp"

class Piece;
class Board;

class Spot {
public:
    // Spot(Board* board);
    Spot(Position pos, Board* board);

    Position getPosition();
    Board* getBoard();
    Piece* getPiece();
    // Spot(std::string name);
    // Spot(int x, int y, Piece& piece);
    std::string cvtPositionToName(Position pos);
    bool isPositionValid(Position pos);
    bool isDark();
    bool isFree();

    void setPiece(Piece *piece);

    friend std::ostream& operator<<(std::ostream& os, const Spot& s);

    // Piece* getPiece();

private:
    Position pos_;
    std::string name_; // e.g. e4, f6
    bool isDark_;

    Board* board_;
    Piece* piece_;
};

#endif  // SPOT_HPP