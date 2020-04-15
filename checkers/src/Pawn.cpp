#include "Pawn.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include "King.hpp"
#include <vector>

Pawn::Pawn(Position pos, bool isWhite, bool isUser, Board& board) : Piece(pos, isWhite, isUser) {
    if (isWhite)
        board.placePiece(pos, WhitePawn);
    else
        board.placePiece(pos, BlackPawn);
}

void Pawn::getCaptureMoves(std::vector<Move> &moves, Board board, Move current) {

    int dx[4] = {1,1,-1,-1};
    int dy[4] = {-1,1,-1,1};

    int countMoves = 0;
    for(int i = 0; i < 4; ++i){
        Position pos(getPosition().x + dx[i], getPosition().y + dy[i]);
        if (pos.isValid()) {
            if (isDiffColor(board.getPieceName(pos))) {
                Position newP = Position(pos.x + dx[i], pos.y + dy[i]);
                if (board.getPieceName(newP) == Empty) {
                    ++countMoves;
                    Move tmp = Move(getPosition(), newP, pos);
                    if (current.isInitial()) current = tmp;
                    else current = current.merge(tmp);
                    board.makeMove(tmp);
                    if (newP.isLastRow(isUser())) {
                        King k(newP, isWhite(), isUser(), board);
                        auto kingMoves = k.getValidMoves(board, true);
                        for (auto& km : kingMoves) {
                            moves.push_back(current.merge(km));
                        }
                        continue;
                    }
                    Pawn p(newP, isWhite(), isUser(), board);
                    p.getCaptureMoves(moves, board, current);
                }
            }
        }
        
    }
}

std::vector<Move> Pawn::getValidMoves(Board &board, bool mustCapture) {

    std::vector<Move> moves;
    Move move;

    getCaptureMoves(moves, board, move);

    if (moves.empty()){
        int d[2] ={1, -1};
        if (isUser()) {
            for(int i = 0 ; i < 2 ; ++i){
                Position nP(getPosition().x + d[i], getPosition().y + 1);
                if(board.getPieceName(nP) == Empty){
                    moves.push_back(Move(pos_, nP));
                }
            }
        }
        else {
            for(int i = 0 ; i < 2 ; ++i){
                Position nP(getPosition().x + d[i], getPosition().y - 1);
                if(board.getPieceName(nP) == Empty){
                    moves.push_back(Move(pos_, nP));
                }
            }
        }
        mustCapture = false;
    }
    return moves;
}

void Pawn::canCapture(std::vector<Move> &moves, Board board, Move current) {};

std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}