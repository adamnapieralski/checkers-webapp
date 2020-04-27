/**
 * @file Pawn.hpp
 * @brief Header file for Pawn class, representing pawn piece.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef PAWN_HPP
#define PAWN_HPP

#include "Piece.hpp"

class Pawn : public Piece {
    using Piece::Piece;
    
public:
    Pawn(Position pos, bool isWhite, bool isUser, Board& board);

    void captureMoves(std::vector<Move>& moves, Board board, Move current) const override;
    std::vector<Move> getCaptureMoves(Board& board) const override;
    std::vector<Move> getValidMoves(Board& board) const override;

    std::ostream& print(std::ostream&) const override;
};

#endif  // PAWN_HPP