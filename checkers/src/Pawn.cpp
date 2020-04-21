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

    auto tmpCurrent = current;
    auto tmpBoard = board;
    auto startPos = getPosition();

    int countMoves = 0;
    for(int i = 0; i < 4; ++i){
        Position capPos(startPos.x + dx[i], startPos.y + dy[i]);
        if (capPos.isValid()) {
            if (isDiffColor(board.getPieceName(capPos))) {
                Position newPos = Position(capPos.x + dx[i], capPos.y + dy[i]);
                if (newPos.isValid() && board.getPieceName(newPos) == Empty) {
                    ++countMoves;
                    Move tmp = Move(startPos, newPos, capPos);

                    if (current.isInitial()) current = tmp;
                    else current = current.merge(tmp);
                    board.makeMove(tmp);
                    if (newPos.isLastRow(isUser())) {
                        current.addChange(newPos);
                        King k(newPos, isWhite(), isUser(), board);
                        k.getCaptureMoves(moves, board, current);
                        current = tmpCurrent;
                        board = tmpBoard;
                        continue;
                    }
                    Pawn p(newPos, isWhite(), isUser(), board);
                    p.getCaptureMoves(moves, board, current);
                    current = tmpCurrent;
                    board = tmpBoard;
                }
            }
        }
    }
    if (countMoves == 0 && !current.isInitial()){
        moves.push_back(current);
    }
}

std::vector<Move> Pawn::getValidMoves(Board &board) {

    std::vector<Move> moves;
    Move move;

    getCaptureMoves(moves, board, move);

    if (moves.empty()){
        int d[2] ={1, -1};
        if (isUser()) {
            for(int i = 0 ; i < 2 ; ++i){
                Position nP(getPosition().x + d[i], getPosition().y + 1);
                if(board.getPieceName(nP) == Empty){
                    moves.push_back(Move(getPosition(), nP));
                }
            }
        }
        else {
            for(int i = 0 ; i < 2 ; ++i){
                Position nP(getPosition().x + d[i], getPosition().y - 1);
                if(board.getPieceName(nP) == Empty){
                    moves.push_back(Move(getPosition(), nP));
                }
            }
        }
    }
    return moves;
}

std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}