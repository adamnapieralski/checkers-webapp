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

/**
 * Class representing King Piece
 * */
class King : public Piece {
    using Piece::Piece;

public:
    King(Position pos, bool isWhite, bool isUser, Board& board);

    //std::shared_ptr<King> clone() const;

    King(const King& k) : Piece(k) {}

    void captureMoves(std::vector<Move>& moves, Board board, Move current) const override;
    std::vector<Move> getCaptureMoves(Board& board) const override;
    std::vector<Move> getNonCaptureMoves(Board& board) const override;

    std::ostream& print(std::ostream&) const override;

private:
    std::shared_ptr<Piece> cloneImplementation() const override;
};

#endif  // KING_H