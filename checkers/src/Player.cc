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

bool Player::isWhite() const {    return isWhite_;    }

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