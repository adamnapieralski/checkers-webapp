/**
 * @file Board.cc
 * @brief Source file for Board class, representing checkers board
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */
#include <map>
#include <algorithm>
#include <iostream>
#include "Board.h"

std::ostream& operator<<(std::ostream& os, const PieceName& p) {
    switch (p){
        case EMPTY : os << "_"; break;
        case WHITE_KING : os << "K"; break ;
        case WHITE_PAWN : os << "w"; break;
        case BLACK_KING : os << "B"; break ;
        case BLACK_PAWN : os << "b"; break ;
        default : os << " "; break ;
    }
    return os;
}

Board::Board() {
    // for(auto i = board_.begin(); i != board_.end(); ++i ){
    //     for(auto j = i->begin(); j != i->end(); ++j ){
    //         *j = EMPTY;
    //     }
    // }
    clear();
    initializePositionNames();
}

Board::Board(std::string fen) {
    std::string fenSlashed = fen + '/';
    int alreadyVisitedIds = 0;
    for (int row = BOARD_SIZE - 1; row >= 0; --row) {
        int j = 0;
        int k = 0;
        while (fenSlashed[alreadyVisitedIds + j] != '/') {
            if (std::isdigit(fenSlashed[alreadyVisitedIds + j])) {
                int max = k + std::stoi(fenSlashed.substr(alreadyVisitedIds + j, 1));
                for (; k < max; ++k) {
                    board_[row][j + k] = EMPTY;
                }
                --k;
            }
            else {
                auto piecePair = std::find_if(fenPiecesNames_.begin(), fenPiecesNames_.end(), [&](const std::pair<PieceName, char> &pair) {
                    return pair.second == fenSlashed[alreadyVisitedIds + j];
                });
                board_[row][j + k] = piecePair->first;
            }
            ++j;
        }
        alreadyVisitedIds += j + 1;
    }
}

void Board::clear() {
    for (auto& row : board_) {
        for (auto& spot : row) {
            spot = EMPTY;
        }
    }
}

void Board::initializePositionNames() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            positionNames_.insert({ positionLetters_.substr(i, 1) + positionNumbers_.substr(j, 1), Position(i, j )});
        }
    }
}

Position Board::getPositionByName(std::string posName) const {
    auto posIt = positionNames_.find(posName);
    if (posIt != positionNames_.end()) {
        return posIt->second;
    }
    else {
        throw std::out_of_range("Position name not valid.");
    }
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for(auto i = b.board_.rbegin(); i != b.board_.rend(); ++i ){
        for(auto j = i->begin(); j != i->end(); ++j ){
            std::cout << *j << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> Board::getBoard() const {
    return board_;
}

void Board::clearPosition(const Position& pos) {
    if (!pos.isValid()) {
        throw std::out_of_range("Invalid position.");
        return;
    }
    board_[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)] = EMPTY;
}

void Board::placePiece(const Position& pos, PieceName piece) {
    if (!pos.isValid()) {
        throw std::out_of_range("Invalid position.");
        return;
    }
    board_[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)] = piece;
}

PieceName Board::getPieceName(const Position& pos) const {
    return board_[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}

bool Board::arePiecesSameColor(PieceName p1, PieceName p2) {
    if (p1 == WHITE_KING || p1 == WHITE_PAWN) {
        if (p2 == WHITE_PAWN || p2 == WHITE_PAWN) {
            return true;
        }
    }
    else if (p1 != EMPTY) {
        if (p2 == BLACK_KING || p2 == BLACK_PAWN) {
            return true;
        }
    }
    return false;
}

bool Board::arePiecesDifferentColor(PieceName p1, PieceName p2) {
    if (p1 == WHITE_KING || p1 == WHITE_PAWN) {
        if (p2 == BLACK_KING || p2 == BLACK_PAWN) {
            return true;
        }
    }
    else if (p1 != EMPTY) {
        if (p2 == WHITE_KING || p2 == WHITE_PAWN) {
            return true;
        }
    }
    return false;
}

void Board::makeMove(const Move& m) {
    auto st = m.getStartPosition();
    if (!st.isValid()) {
        throw std::out_of_range("Invalid position.");
        return;
    }
    auto pc = getPieceName(st);
    clearPosition(st);
    for (auto& c : m.getCapturedPositions()) { clearPosition(c); }
    placePiece(m.getEndPosition(), pc);
}

Move Board::findUserMove(const Position& origin, const Position& destination) {
    if (getPieceName(destination) != EMPTY || getPieceName(origin) == EMPTY) return Move();
    auto diffUnit = (destination - origin).getUnitPosition();
    if (diffUnit.isZero()) return Move();
    auto checkPos = origin + diffUnit;

    auto foundMove = Move(origin, destination);
    if (destination.isLastRow(true)) {
        foundMove.addUpgradePosition(destination);
    }
    while (checkPos != destination) {
        if (arePiecesDifferentColor(getPieceName(checkPos), getPieceName(origin))) {
            foundMove.addCapturedPosition(checkPos);
        
            return foundMove;
        }
        checkPos += diffUnit;
    }
    return foundMove;
}

Board& Board::operator=(Board other) {
    swap(*this, other);
    return *this;
}

std::string Board::getFEN() const {
    std::map<enum PieceName, char>  fenPiecesNames_ = {
        { EMPTY, 'e' }, { WHITE_PAWN , 'P' }, { WHITE_KING, 'K' }, { BLACK_PAWN, 'p' }, { BLACK_KING, 'k' }
    };
    std::string fen = "";
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            fen += fenPiecesNames_[board_[BOARD_SIZE - 1 -row][col]];
        }
        fen += '/';
    }
    fen.pop_back();
    size_t eCount = 0;
    size_t i;
    for (i = 0; i < fen.length(); ++i) {
        if (fen[i] == 'e') {
            eCount++;
        }
        else if (eCount > 0) {
            fen = fen.replace(i - eCount, eCount, std::to_string(eCount));
            i -= eCount + 1;
            eCount = 0;
        }
    }
    if (eCount > 0) fen = fen.replace(i - eCount, eCount, std::to_string(eCount));
    return fen;
}

void swap(Board& b1, Board& b2) {
    std::swap(b1.board_, b2.board_);
}