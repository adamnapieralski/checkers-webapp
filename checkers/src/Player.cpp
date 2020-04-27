/**
 * @file Player.cpp
 * @brief Source file for Player class, representing player.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include "Player.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include <algorithm> 

#define INIT_ROW 3

Player::Player(bool isWhite, bool isUser) :
    isWhite_(isWhite), isUser_(isUser) {}

bool Player::isWhite() const {    return isWhite_;    }

void Player::initializePieces(Board& board){
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

void Player::addPiece(bool isKing, Position pos, Board& board){
    if(isKing) pieces_.push_back(std::make_shared<King>(pos, isWhite_, isUser_, board));
    else pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, isUser_, board));
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