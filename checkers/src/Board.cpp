#include "Board.hpp"
#include "Pawn.hpp"

Board::Board() {
    for (int i = 0; i < sizeY_; ++i) {
        std::vector<Spot> row;
        for (int j = 0; j < sizeX_; ++j) {
            row.push_back(Spot(Position(j, i), this));
        }
        spots_.push_back(row);
    }
}

void Board::initialize(Player &user, Player &computer) {
    bool isUserWhite = user.isWhite();
    // create and set user's pieces
    for (auto row = spots_.begin(); row != spots_.begin() + 3; ++row) {
        for (auto spot = row->begin(); spot != row->end(); ++spot) {
            if (spot->isDark()) {
                Pawn* pawn = new Pawn(*spot, isUserWhite);
                user.addPiece(pawn);
            }
        }
    }
    // create and set computer's pieces
    for (auto row = spots_.end() - 3; row != spots_.end(); ++row) {
        for (auto spot = row->begin(); spot != row->end(); ++spot) {
            if (spot->isDark()) {
                Pawn* pawn = new Pawn(*spot, !isUserWhite);
                computer.addPiece(pawn);
            }
        }
    }

}

Spot& Board::getSpotOnPosition(Position pos) {
    return spots_[pos.y][pos.x];
}

bool Board::isMoveValid(Position origin, Position dest) {
    if (getSpotOnPosition(origin).isDark() || !getSpotOnPosition(dest).isDark()) return false;
    if (getSpotOnPosition(origin).isFree() || !getSpotOnPosition(dest).isFree()) return false;
    
    return false;
}

std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (auto row = b.spots_.rbegin(); row != b.spots_.rend(); ++row) {
        for (auto spot = row->begin(); spot != row->end(); ++spot) {
            std::cout << *spot << " ";
        }
        std::cout << std::endl;
    }
    return os;
}