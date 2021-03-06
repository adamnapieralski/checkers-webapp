/**
 * @file Pawn.h
 * @brief Header file for Pawn class, representing pawn piece.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

/**
 * Class representing pawn Piece
 * */
class Pawn : public Piece {
    using Piece::Piece;
    
public:
    Pawn(Position pos, bool isWhite, bool isUser, Board& board);

    Pawn(const Pawn& p) : Piece(p) {}

    void captureMoves(std::vector<Move>& moves, Board board, Move current) const override;
    std::vector<Move> getCaptureMoves(Board& board) const override;
    std::vector<Move> getNonCaptureMoves(Board& board) const override;

    std::ostream& print(std::ostream&) const override;

private:
    std::shared_ptr<Piece> cloneImplementation() const override;
};

#endif  // PAWN_H