/**
 * Projekt Zaawansowane Programowanie w C++ - Warcaby
 * 24.04.2020
 * 
 * Autorzy: Patrycja Cieplicka, Adam Napieralski
 * 
 * Plik nagłówkowy klasy abstrakcyjnej Piece, która reprezntuje wszystkie figury warcabowe
 * 
 * */

#ifndef PIECE_HPP
#define PIECE_HPP

#include <string>
#include <vector>

#include "Position.hpp"
#include "Move.hpp"
#include "Board.hpp"

// to resolve: class Piece has virtual funcs and accessible non-virtual destructor
class Piece {
public:
    // Piece(Position pos, bool isWhite, Board* board);
    Piece(Position pos, bool isWhite, bool isUser);
    virtual ~Piece() {};

    bool isWhite() const;
    bool isUser() const;
    
    Position getPosition() const;
    void changePosition(Position pos);

    bool isSameColor(PieceName &pn) const;
    bool isDiffColor(PieceName pn) const;
    
    virtual std::vector<Move> getValidMoves(Board& board) const = 0;
    virtual void captureMoves(std::vector<Move> &moves, Board board, Move current) const  = 0;
    virtual std::vector<Move> getCaptureMoves(Board& board) const = 0;
    virtual std::ostream& print(std::ostream& os) const = 0;

protected:
    Position pos_;

private:
    bool isWhite_;
    bool isUser_;
};

#endif  // PIECE_HPP