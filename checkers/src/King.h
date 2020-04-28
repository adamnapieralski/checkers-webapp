/**
 * @file King.h
 * @brief Header file for King class, representing king piece.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    using Piece::Piece;

public:
    King(Position pos, bool isWhite, bool isUser, Board& board);

    void captureMoves(std::vector<Move>& moves, Board board, Move current) const override;
    std::vector<Move> getCaptureMoves(Board& board) const override;
    std::vector<Move> getNonCaptureMoves(Board& board) const override;

    std::ostream& print(std::ostream&) const override;
};

#endif  // KING_H