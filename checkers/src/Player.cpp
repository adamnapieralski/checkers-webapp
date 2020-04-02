#include "Player.hpp"
#include "Pawn.hpp"

bool Player::isWhite() {    return isWhite_;    }

void Player::initializePieces(){
    /*for(auto i = board_.getBoard.begin(); i =! board_.getBoard.begin() + 3; ++i){
        for(auto j = (*i).begin(); j =! (*i).end(); ++j ){

        }
    }*/
    if (isWhite_){
        for(int i = 0; i < 3; ++i){
            for(int j = 0; j < 8; ++j){
                if( (i + j + 1) % 2 ){
                    Pawn* pawn = new Pawn(isWhite_, Position(i,j), *board_);
                }
            }
        }
    }
    else {
        for(int i = 7; i > 4; --i){
            for(int j = 0; j < 8; ++j){
                if( (i + j + 1) % 2 ){
                    Pawn* pawn = new Pawn(isWhite_, Position(i,j), *board_);
                }
            }
        }
    }

}

//napisac desktruktor zwalniajacy te pionki
