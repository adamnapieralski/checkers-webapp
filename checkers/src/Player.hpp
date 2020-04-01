#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>

#include "Piece.hpp"
#include "Board.hpp"

class Player {
public:
    Player(Board* board){ board_ = board;};
    bool isWhite();
    void setIsWhite(bool isWhite);
    void addPiece(Piece* piece);
    void setHasTurn(bool hasTurn);
    bool movePiece(Piece* piece, Position pos);
    Piece* getPlayerPiece();

private:

    Board* board_;
    std::vector<Piece*> pieces_;
    bool hasTurn_;
    bool isWhite_;
};

#endif  // PLAYER_HPP