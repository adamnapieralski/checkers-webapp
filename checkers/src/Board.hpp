/**
 * Projekt Zaawansowane Programowanie w C++ - Warcaby
 * 24.04.2020
 * 
 * Autorzy: Patrycja Cieplicka, Adam Napieralski
 * 
 * Plik nagłówkowy klasy Board, która reprezentuje plansze do gry w Warcaby
 * 
 * */

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

    std::string getFEN();

    Board& operator=(Board other);

    friend void swap(Board& b1, Board& b2);
    friend std::ostream& operator<<(std::ostream& os, const Board& b);
    friend std::ostream& operator<<(std::ostream& os, const PieceName& p);

private:
    std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> board_ ;
};

#endif  // BOARD_HPP