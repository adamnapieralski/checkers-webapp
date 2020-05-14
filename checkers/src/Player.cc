/**
 * @file Player.cc
 * @brief Source file for Player class, representing player.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include "Player.h"
#include "Pawn.h"
#include "King.h"
#include <algorithm> 

Player::Player(bool isWhite) : isWhite_(isWhite) {}

Player::Player(const Player& p) {

    for (auto& piece : p.pieces_){
        this->pieces_.push_back(piece->clone());
    }
    name_ = p.name_;
    isWhite_ = p.isWhite_;
    hasTurn_ = p.hasTurn_;
}

Player& Player::operator=(const Player& p) {
    
    if( this -> pieces_.size() > 0 ){
        for (auto& piece : pieces_){
            erasePiece(piece);
        }
    }
    
    if (this != &p) {
        for (auto& piece : p.pieces_){
            this->pieces_.push_back(piece->clone());
        }
        name_ = p.name_;
        isWhite_ = p.isWhite_;
        hasTurn_ = p.hasTurn_;
    }
    return *this;
}

bool Player::isWhite() const {
    return isWhite_;
}

std::string Player::getName() const {
    return name_;
}

void Player::setIsWhite(bool isWhite) {
    isWhite_ = isWhite;
}

void Player::setName(std::string name) {
    name_ = name;
}

std::vector<std::shared_ptr<Piece>> Player::getPieces() const{
    return pieces_;
}

std::vector<std::vector<Move>> Player::getValidMoves(Board& board) const{
    std::vector<std::vector<Move>> valid_moves;
    for (auto pc : pieces_){
        auto mvs = pc->getCaptureMoves(board);
        if(!mvs.empty()) valid_moves.push_back(mvs);
    }
    if(valid_moves.empty()){
        for (auto pc : pieces_){
            auto mvs = pc->getNonCaptureMoves(board);
            if(!mvs.empty()) valid_moves.push_back(mvs);
        }
    }
    return valid_moves;
}

void Player::erasePiece(std::shared_ptr<Piece> piece){
    pieces_.erase(std::remove_if(pieces_.begin(), pieces_.end(), 
                                            [&piece](const std::shared_ptr<Piece> &p) {return p && p == piece ; }));
}

void Player::changePiece(std::shared_ptr<Piece> piece, const Position& pos){
    piece->changePosition(pos);
}

void Player::movePiece(Board& board, Player& opponent, const Move& move) {
    auto start = move.getStartPosition();
    auto tmp = findPiece(start);

    if(!move.getUpgradePositions().empty()){
        erasePiece(tmp);
        addPiece(true, start, board);
    }
    findPiece(start)->changePosition(move.getEndPosition());
    if(!move.getCapturedPositions().empty())
        for (auto& c : move.getCapturedPositions()) {
            opponent.erasePiece(opponent.findPiece(c));
        }
    board.makeMove(move);
}

std::shared_ptr<Piece> Player::findPiece(const Position& pos) const {
    for (auto& piece : pieces_){
        if (piece->getPosition() == pos) return piece;
    }
    return nullptr;
}

int Player::getNumberOfPawns(Board& board){
    int pawns = 0;

    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            if (isWhite_){
                if (board.getPieceName(Position(row,col)) == WHITE_PAWN ) pawns++;
            }
            else{
                if (board.getPieceName(Position(row,col)) == BLACK_PAWN ) pawns++;
            }
        }
    }

    return pawns;
}

int Player::getNumberOfKings(Board& board){
    int kings = 0;

    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            if (isWhite_){
                if (board.getPieceName(Position(row,col)) == WHITE_KING ) kings++;
            }
            else{
                if (board.getPieceName(Position(row,col)) == BLACK_KING ) kings++;
            }
        }
    }
    return kings;
}

