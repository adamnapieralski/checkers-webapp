/**
 * Projekt Zaawansowane Programowanie w C++ - Warcaby
 * 24.04.2020
 * 
 * Autorzy: Patrycja Cieplicka, Adam Napieralski
 * 
 * Plik nagłówkowy King, która reprezentuje damkę w warcabach
 * 
 * */


#ifndef KING_HPP
#define KING_HPP

#include "Piece.hpp"

class King : public Piece {
    using Piece::Piece;

public:
    King(Position pos, bool isWhite, bool isUser, Board& board);

    void captureMoves(std::vector<Move> &moves, Board board, Move current) const override;
    std::vector<Move> getCaptureMoves(Board& board) const override;
    std::vector<Move> getValidMoves(Board& board) const override;

    std::ostream& print(std::ostream&) const override;
};

#endif  // KING_HPP