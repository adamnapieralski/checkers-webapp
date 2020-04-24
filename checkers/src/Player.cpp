#include "Player.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include <algorithm> 

Player::Player(bool isWhite, bool isUser) :
    isWhite_(isWhite), isUser_(isUser) {}

bool Player::isWhite() {    return isWhite_;    }

void Player::initializePieces(Board &board){
    // place in lower part for user
    if (isUser_) {
        for (int i = 0; i < 3; ++i){
            for(int j = 0; j < 8; ++j) {
                if ((i + j) % 2 == 0) {
                    pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, isUser_, board));
                }
            }
        }
    }
    // place in upper part for computer
    else {
        for (int i = 7; i > 4; --i){
            for (int j = 0; j < 8; ++j){
                if ((i + j) % 2 == 0){
                    pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, isUser_, board));
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Piece>> Player::getPieces(){
    return pieces_;
}

std::vector<std::vector<Move>> Player::getValidMoves(Board &board){
    std::vector<std::vector<Move>> valid_moves;
    std::vector<Move> tmp;
    for (auto i = pieces_.begin(); i != pieces_.end(); ++i){
        tmp = (*i) ->getCaptureMoves(board);
        if(!tmp.empty()) valid_moves.push_back(tmp);
    }
    if(valid_moves.empty()){
        for (auto i = pieces_.begin(); i != pieces_.end(); ++i){
            tmp = (*i) -> getValidMoves(board);
            if(!tmp.empty()) valid_moves.push_back(tmp);
        }
    }
    return valid_moves;
}

/*std::vector<Move> Player::getValidMovePiece(Board &board, int index){
    std::vector<Move> move;
    move = (pieces_[index])->getCaptureMoves(board);
    if(move.empty()) (pieces_[index]) ->getValidMoves(board);

    return move;
}*/

void Player::printPlayer(){
    for (size_t i = 0; i < 12; i++){
        std::cout << pieces_[i]->getPosition().x << "," << pieces_[i]->getPosition().y << std::endl; 
    }
}

void Player::erasePiece(std::shared_ptr<Piece> piece){
    pieces_.erase(std::remove_if(pieces_.begin(), pieces_.end(), 
                                            [&piece](std::shared_ptr<Piece> p) {return p && p == piece ; }));
}

void Player::changePiece(std::shared_ptr<Piece> piece, Position pos){
    piece->changePosition(pos);
}

void Player::addPiece(bool isKing, Position pos, Board &board){
    if(isKing) pieces_.push_back(std::make_shared<King>(pos, isWhite_, isUser_, board));
    else pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, isUser_, board));
}

void Player::movePiece(Board &board, Player &opponent, Move move){
    auto tmp = findPiece(move.getStartPosition());
    if(!move.getChangedPosition().empty()){
        erasePiece(tmp);
        addPiece(true,move.getStartPosition(),board);
        tmp = findPiece(move.getStartPosition());
        if(!tmp) throw std::out_of_range("Nie znaleziona pionka na podanej pozycji");
    }
    changePiece(tmp , move.getEndPosition() );
    if(!move.getCapturedPositions().empty())
        for (auto& c : move.getCapturedPositions()) {
            opponent.erasePiece(opponent.findPiece(c));
        }
    board.makeMove(move);
}

std::shared_ptr<Piece> Player::findPiece(Position pos){
    for (auto& piece : pieces_){
        if (piece->getPosition() == pos) return piece;
    }
    return nullptr;
}