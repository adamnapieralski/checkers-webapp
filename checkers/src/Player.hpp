#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Piece.hpp"

class Player {
public:
    bool isWhite();
    void setIsWhite(bool isWhite);
    void addPiece(Piece* piece);
    void setHasTurn(bool hasTurn);

private:
    std::vector<Piece*> pieces_;
    bool hasTurn_;
    bool isWhite_;
};

#endif  // PLAYER_HPP