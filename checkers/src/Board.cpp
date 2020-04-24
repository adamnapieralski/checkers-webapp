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

std::array<std::array<PieceName,BOARD_SIZE>,BOARD_SIZE> Board::getBoard(){
    return board_;
}

void Board::clearPosition(Position pos) {
    if (!pos.isValid()) {
        throw std::out_of_range("Nieprawidłowa pozycja");
        return;
    }
    board_[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)] = EMPTY;
}

void Board::placePiece(Position pos, PieceName piece){
    if (!pos.isValid()) {
        throw std::out_of_range("Nieprawidłowa pozycja");
        return;
    }
    board_[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)] = piece;
}

PieceName Board::getPieceName(Position pos) {
    return board_[static_cast<size_t>(pos.y)][static_cast<size_t>(pos.x)];
}

void Board::makeMove(const Move& m) {
    auto st = m.getStartPosition();
    if (!st.isValid()) {
        throw std::out_of_range("Nieprawidłowa pozycja");
        return;
    }
    auto pc = board_[static_cast<size_t>(st.y)][static_cast<size_t>(st.x)];
    board_[static_cast<size_t>(st.y)][static_cast<size_t>(st.x)] = EMPTY;
    for (auto& c : m.getCapturedPositions()) {
        board_[static_cast<size_t>(c.y)][static_cast<size_t>(c.x)] = EMPTY;
    }
    auto en = m.getEndPosition();
    if (!en.isValid()) {
        throw std::out_of_range("Nieprawidłowa pozycja");
        return;
    }
    board_[static_cast<size_t>(en.y)][static_cast<size_t>(en.x)] = pc;
}

Board& Board::operator=(Board other) {
    swap(*this, other);
    return *this;
}

std::string Board::getFEN() {
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

// void Board::makeMove(const Move &move){

//     auto st = move.startPos;
//     auto pc = board_[st.x][st.y];
//     board_[st.x][st.y] = Empty;
//     for (auto& c : move.capturedPos) {
//         board_[c.x][c.y] = Empty;
//     }
//     auto en = move.endPos;
//     board_[en.x][en.y] = pc;
// }

void swap(Board& b1, Board& b2) {
    std::swap(b1.board_, b2.board_);
}