#include "Player.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include <algorithm> 

Player::Player(Board* board, bool isWhite, bool isUser) :
    board_(board), isWhite_(isWhite), isUser_(isUser) {}


bool Player::isWhite() {    return isWhite_;    }

void Player::initializePieces(){
    // place in lower part for user
    if (isUser_) {
        for (int i = 0; i < 3; ++i){
            for(int j = 0; j < 8; ++j) {
                if ((i + j) % 2 == 0) {
                    pieces_.push_back(new Pawn(Position(j, i), isWhite_, isUser_, *board_));
                }
            }
        }
    }
    // place in upper part for computer
    else {
        for (int i = 7; i > 4; --i){
            for (int j = 0; j < 8; ++j){
                if ((i + j) % 2 == 0){
                   pieces_.push_back(new Pawn(Position(j, i), isWhite_, isUser_, *board_));
                }
            }
        }
    }
}

void Player::addPiece(bool isKing, Position pos, Board &board){
    if(isKing)
        pieces_.push_back(new King(pos, isWhite_, isUser_, *board_));
    else pieces_.push_back(new Pawn(pos, isWhite_, isUser_, *board_));
}

std::vector<Move> Player::getValidMoves(Board &board, int index){
    /*std::vector<std::vector<Move>> valid_moves;
    std::vector<std::vector<Move>> only_capture;
    std::vector<Move> tmp;
    bool mustCapture;
    bool ifOnlyCapture = false;
    for (auto i = pieces_.begin(); i != pieces_.end(); i++){
        tmp = (*i)->getValidMoves(board,mustCapture);
        if(mustCapture){
            only_capture.push(tmp);
            ifOnlyCapture = true;
        }
        if(!ifOnlyCapture) valid_moves.push_back(tmp);
    }

    if(ifOnlyCapture) return only_capture;
    return valid_moves;
    
    */
    std::vector<Move> move;
    //std::cout << pieces_[index]->getPosition().x << "," << pieces_[index]->getPosition().y << std::endl;
    bool mustCapture;
    move = (pieces_[index])->getValidMoves(board, mustCapture);

    return move;
}

void Player::printPlayer(){
    for (int i = 0; i < 12; i++){
        std::cout << pieces_[i]->getPosition().x << "," << pieces_[i]->getPosition().y << std::endl; 
    }
}

void Player::erasePiece(Piece* piece){
    pieces_.erase(std::remove_if(pieces_.begin(), pieces_.end(), 
                                            [&piece](Piece* p) {return p && p == piece ; }));
}

void Player::changePiece(Piece* piece, Position pos){
    piece ->changePosition(pos);
}

void Player::movePiece(Board &board, Player &opponent, Move move){
    Piece* tmp = findPiece( move.getStartPosition() );
    if(!move.getChangedPosition().empty()){
        erasePiece(tmp);
        pieces_.push_back(new King(move.getStartPosition(), isUser_, isWhite_, board));
        tmp = findPiece(move.getStartPosition());
    }
    changePiece(tmp , move.getEndPosition() );
    if(!move.getCapturedPositions().empty())
        for (auto& c : move.getCapturedPositions()) {
            opponent.erasePiece(opponent.findPiece(c));
        }
    board.makeMove(move);
}
//napisac desktruktor zwalniajacy te pionki

Piece* Player::findPiece(Position pos){
    for (auto& piece : pieces_){
        if (piece->getPosition() == pos) return piece;
    }
    return nullptr;
}