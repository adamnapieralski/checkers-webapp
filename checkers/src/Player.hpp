#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>

#include "Piece.hpp"
#include "Board.hpp"

class Player {
public:

    Player(Board* board, bool isWhite){board_ = board; isWhite_ = isWhite;};
    Player(){};
    bool isWhite();
    void setHasTurn(bool hasTurn);
    void initializePieces();

private:
    std::vector<Piece*> pieces_;
    Board* board_;
    bool hasTurn_;
    bool isWhite_;
};

#endif  // PLAYER_HPP