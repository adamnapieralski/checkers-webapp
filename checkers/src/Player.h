#ifndef Player_h
#define Player_h

#include <vector>

#include "Piece.h"

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

#endif