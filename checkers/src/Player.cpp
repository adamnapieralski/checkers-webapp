#include "Player.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include <algorithm> 

#define INIT_ROW 3

Player::Player(bool isWhite, bool isUser) :
    isWhite_(isWhite), isUser_(isUser) {}

bool Player::isWhite() const {    return isWhite_;    }

void Player::initializePieces(Board &board){
    // place in lower part for user
    if (isUser_) {
        for (int i = 0; i < INIT_ROW; ++i){
            for(int j = 0; j < BOARD_SIZE; ++j) {
                if ((i + j) % 2 == 0) {
                    pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, isUser_, board));
                }
            }
        }
    }
    // place in upper part for computer
    else {
        for (int i = BOARD_SIZE - 1; i > INIT_ROW + 1; --i){
            for (int j = 0; j < BOARD_SIZE; ++j){
                if ((i + j) % 2 == 0){
                    pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, isUser_, board));
                }
            }
        }
    }
}

std::vector<std::shared_ptr<Piece>> Player::getPieces() const{
    return pieces_;
}

std::vector<std::vector<Move>> Player::getValidMoves(Board &board) const{
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

/*void Player::printPlayer(){
    for (size_t i = 0; i < 12; i++){
        std::cout << pieces_[i]->getPosition().x << "," << pieces_[i]->getPosition().y << std::endl; 
    }
}*/

void Player::erasePiece(std::shared_ptr<Piece> piece){
    pieces_.erase(std::remove_if(pieces_.begin(), pieces_.end(), 
                                            [&piece](const std::shared_ptr<Piece> &p) {return p && p == piece ; }));
}

void Player::changePiece(std::shared_ptr<Piece> piece, Position pos){
    piece->changePosition(pos);
}

void Player::addPiece(bool isKing, Position pos, Board &board){
    if(isKing) pieces_.push_back(std::make_shared<King>(pos, isWhite_, isUser_, board));
    else pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, isUser_, board));
}

void Player::movePiece(Board &board, Player &opponent, Move move){
    auto start = move.getStartPosition();
    //auto tmp = findPiece(start);
    auto it = std::find_if(pieces_.begin(), pieces_.end(), 
                    [&start](const std::shared_ptr<Piece> &p) {return p->getPosition() == start; });
    if(it == pieces_.end()) throw std::out_of_range("Nie znaleziona pionka na podanej pozycji");

    if(!move.getChangedPosition().empty()){
        pieces_.erase(it); 
        //erasePiece(tmp);
        addPiece(true,start,board);
        it = std::find_if(pieces_.begin(), pieces_.end(), 
                    [&start](const std::shared_ptr<Piece> &p) {return p->getPosition() == start; });
        //tmp = findPiece(start);
        if(it == pieces_.end()) throw std::out_of_range("Nie znaleziona pionka na podanej pozycji");
    }
    (*it)->changePosition(move.getEndPosition());
    //changePiece(tmp , move.getEndPosition() );
    if(!move.getCapturedPositions().empty())
        for (auto& c : move.getCapturedPositions()) {
            opponent.erasePiece(opponent.findPiece(c));
        }
    board.makeMove(move);
}


std::shared_ptr<Piece> Player::findPiece(Position &pos) const{
    for (auto& piece : pieces_){
        if (piece->getPosition() == pos) return piece;
    }

    

    return nullptr;
}