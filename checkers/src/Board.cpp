#include <map>
#include "Board.hpp"

Board::Board(){
    /* board_={ {
    { { BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty } },
    { { Empty, BlackPawn, Empty, BlackPawn, Empty,BlackPawn , Empty, BlackPawn } },
    { { BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty } },
    { { Empty, Empty, Empty, Empty, Empty, Empty, Empty,Empty } },
    { { Empty, Empty, Empty, Empty, Empty, Empty, Empty,Empty } },
    { { WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty } },
    { { Empty, WhitePawn, Empty, WhitePawn, Empty, WhitePawn ,Empty, WhitePawn } },
    { { WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty } },
    } };*/
    for(auto i = board_.begin(); i != board_.end(); ++i ){
        for(auto j = i->begin(); j != i->end(); ++j ){
            *j = Empty;
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

std::array<std::array<PieceName,8>,8> Board::getBoard(){
    return board_;
}

void Board::placePiece(Position pos, PieceName piece){
    if(board_[pos.x][pos.y] == Empty){
        board_[pos.x][pos.y] = piece;
    }
}

std::string Board::getFEN() {
    std::map<enum PieceName, char>  pcs = {
        { Empty, 'e' }, { WhitePawn , 'p' }, { WhiteKing, 'k' }, { BlackPawn, 'P' }, { BlackKing, 'K' }
    };
    std::string fen = "";
    for (int row = 7; row >=0; --row) {
        for (int col = 0; col < 8; ++col) {
            fen += pcs[board_[row][col]];
        }
        fen += '/';
    }
    fen.pop_back();
    int eCount = 0;
    int i;
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

void Board::makeMove(Move &move){

    auto st = move.startPos;
    auto pc = board_[st.x][st.y];
    board_[st.x][st.y] = Empty;
    for (auto& c : move.capturedPos) {
        board_[c.x][c.y] = Empty;
    }
    auto en = move.endPos;
    board_[en.x][en.y] = pc;
}
