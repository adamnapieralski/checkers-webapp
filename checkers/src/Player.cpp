#include "Player.hpp"
#include "Pawn.hpp"

Player::Player(Board* board, bool isWhite, bool isUser) :
    board_(board), isWhite_(isWhite), isUser_(isUser) {}


bool Player::isWhite() {    return isWhite_;    }

void Player::initializePieces(){
    // place in lower part for user
    if (isUser_) {
        for (int i = 0; i < 3; ++i){
            for(int j = 0; j < 8; ++j) {
                if ((i + j) % 2 == 0) {
                    pieces_.push_back(new Pawn(isWhite_, Position(i, j), *board_));
                }
            }
        }
    }
    // place in upper part for computer
    else {
        for (int i = 7; i > 4; --i){
            for (int j = 0; j < 8; ++j){
                if ((i + j) % 2 == 0){
                   pieces_.push_back(new Pawn(isWhite_, Position(i, j), *board_));
                }
            }
        }
    }
}

std::vector<Move> Player::getValidMoves(Board &board){
    /*std::vector<std::vector<Move>> valid_moves;
    for (auto i = pieces_.begin(); i != pieces_.end(); i++){
        valid_moves.push_back((*i)->getValidMoves);
    }*/
    std::vector<Move> move;
    std::cout << pieces_[9]->getPosition().x << "," << pieces_[9]->getPosition().y << std::endl;
    move = (pieces_[9])->getValidMoves(board);

    return move;
}
//napisac desktruktor zwalniajacy te pionki
