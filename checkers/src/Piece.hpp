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

    bool isWhite();
    bool isUser();
    
    Position getPosition();

    bool isOnSameDiagonal(Piece& piece);
    // int radiusDistance(Piece& piece);
    Position positionDistance(Position pos);
    void changePosition(Position pos);

    bool isSameColor(PieceName pn);
    bool isDiffColor(PieceName pn);
    
    virtual std::vector<Move> getValidMoves(Board& board) = 0;
    virtual void captureMoves(std::vector<Move> &moves, Board board, Move current) = 0;
    virtual std::vector<Move> getCaptureMoves(Board& board) = 0;
    virtual std::ostream& print(std::ostream& os) = 0;

protected:
    Position pos_;

private:
    bool isWhite_;
    bool isUser_;
};

#endif  // PIECE_HPP