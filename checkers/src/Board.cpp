/**
 * @file Board.cpp
 * @brief Source file for Board class, representing checkers board
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */
#include <map>
#include "Board.hpp"

std::ostream& operator<<(std::ostream& os, const PieceName& p){
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

Board::Board(){
    for(auto i = board_.begin(); i != board_.end(); ++i ){
        for(auto j = i->begin(); j != i->end(); ++j ){
            *j = EMPTY;
        }
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

Board& Board::operator=(Board other) {
    swap(*this, other);
    return *this;
}

std::string Board::getFEN() const {
    std::map<enum PieceName, char>  pcs = {
        { EMPTY, 'e' }, { WHITE_PAWN , 'p' }, { WHITE_KING, 'k' }, { BLACK_PAWN, 'P' }, { BLACK_KING, 'K' }
    };
    std::string fen = "";
    for (size_t row = 0; row < BOARD_SIZE; ++row) {
        for (size_t col = 0; col < BOARD_SIZE; ++col) {
            fen += pcs[board_[BOARD_SIZE - 1 -row][col]];
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