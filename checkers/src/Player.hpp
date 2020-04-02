#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <memory>

#include "Piece.hpp"
#include "Board.hpp"

class Player {
public:

    Player(){};
    bool isWhite();
    void setIsWhite(bool isWhite);
    void setHasTurn(bool hasTurn);

private:
    std::vector<Piece*> pieces_;
    bool hasTurn_;
    bool isWhite_;
};

#endif  // PLAYER_HPP