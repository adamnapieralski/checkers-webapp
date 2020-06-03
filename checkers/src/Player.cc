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

/**
* Get all valid moves for owned pieces on board, respecting the rule of capture obligation.
*/
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

/**
 * This function delete piece from owned Pieces
 * @param piece shared pointer to piece which should be deleted
 * */
void Player::erasePiece(std::shared_ptr<Piece> piece){
    pieces_.erase(std::remove_if(pieces_.begin(), pieces_.end(), 
                                            [&piece](const std::shared_ptr<Piece> &p) {return p && p == piece ; }));
}

/**
 * This function change position of the Piece
 * @param piece shared pointer to piece which position should be changed
 * @param pos where piece should be placed
 * */
void Player::changePiece(std::shared_ptr<Piece> piece, const Position& pos){
    piece->changePosition(pos);
}

/**
 * This function makes Move on board. It changes the state of board and two players.
 * @param board game board
 * @param opponent opponent player
 * @param move move to make
 * */
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

/**
 * @param pos given position
 * @return shared to pointer to piece on given position or nullptr if there is no piece on this position
 * */
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

bool Player::canCapture(Board& board) const {
    for (auto pc : pieces_){
        auto mvs = pc->getCaptureMoves(board);
        if(!mvs.empty()) return true;
    }
    return false;
}

/**
 * This function checks if given move is valid
 * */
bool Player::isMoveValid(const Move& move, Board& board) const {
    auto movedPiece = findPiece(move.getStartPosition());
    if (!movedPiece) return false;
    auto moves = movedPiece->getCaptureMoves(board);
    if (canCapture(board) && moves.empty()) {
        return false;
    }
    else if (moves.empty()) {
        moves = movedPiece->getNonCaptureMoves(board);
    }
    for (auto& pieceMove : moves) {
        if (pieceMove.containsAsStep(move) || pieceMove == move) {
            return true;
        }
    }
    return false;
}

/**
 * This function checks if next captured move exist
 * */
bool Player::isMoveMultiple(const Move& move, Board& board) const {
    auto movedPiece = findPiece(move.getStartPosition());
    if (!movedPiece) return false;
    auto moves = movedPiece->getCaptureMoves(board);
    if (moves.size()) {
        for (auto& pieceMove : moves) {
            if (pieceMove.containsAsStep(move)) {
                return true;
            }
        }
    }
    return false;
}


void Player::initializePiecesFromBoardPerUser(Board& board, bool isUser) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto pos = Position(j, i);
            auto pcName = board.getPieceName(pos);
            if (isWhite_) {
                if (pcName == WHITE_PAWN) {
                    pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, isUser, board));
                }
                if (pcName == WHITE_KING) {
                    pieces_.push_back(std::make_shared<King>(pos, isWhite_, isUser, board));
                }
            }
            else {
                if (pcName == BLACK_PAWN) {
                    pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, isUser, board));
                }
                if (pcName == BLACK_KING) {
                    pieces_.push_back(std::make_shared<King>(pos, isWhite_, isUser, board));
                }
            }

        }
    }
}


