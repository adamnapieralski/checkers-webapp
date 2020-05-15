/**
 * @file Piece.h
 * @brief Header file for abstract Piece class, representing piece.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <memory>

#include "Position.h"
#include "Move.h"
#include "Board.h"

// to resolve: class Piece has virtual funcs and accessible non-virtual destructor
class Piece {
public:
    // Piece(Position pos, bool isWhite, Board* board);
    Piece(Position pos, bool isWhite, bool isUser);
    virtual ~Piece() {};

    std::shared_ptr<Piece> clone() const;

    bool isWhite() const;
    bool isUser() const;
    
    Position getPosition() const;
    void changePosition(Position pos);

    bool isSameColor(PieceName &pn) const;
    bool isDiffColor(PieceName pn) const;


    /**
     * @brief Recursive method finding all possible capture moves.
     * 
     * @param moves vector of moves that will be overwritten with found capture moves
     * @param board board on which moves can be done
     * @param current move already done to the moment of method call
     */
    virtual void captureMoves(std::vector<Move> &moves, Board board, Move current) const  = 0;
    
    virtual std::vector<Move> getNonCaptureMoves(Board& board) const = 0;
    virtual std::vector<Move> getCaptureMoves(Board& board) const = 0;

    virtual std::ostream& print(std::ostream& os) const = 0;

protected:
    Position pos_;

    virtual std::shared_ptr<Piece> cloneImplementation() const = 0;

private:
    bool isWhite_;
    bool isUser_;


};

#endif  // PIECE_H