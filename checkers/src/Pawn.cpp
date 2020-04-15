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
                    Move tmp = Move(getPosition(), pos, newP);
                    if (current.isInitial()) current = tmp;
                    else current = current.merge(tmp);
                    board.makeMove(tmp);
                    if (pos.isLastRow(isUser())) {
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
            // if (isWhite()){
            //     if(board.getBoard()[pos.x][pos.y] == BlackPawn || board.getBoard()[pos.x][pos.y] == BlackKing ){
            //         Position diff = positionDistance(pos);
            //         Position newP = Position(pos.x + diff.x, pos.y + diff.y);
            //         if (board.getBoard()[newP.x][newP.y] == Empty){
            //             countMoves++;
            //             Move tmp = Move(pos_, newP, pos);
            //             current.addStepMove(tmp);
            //             board.makeMove(tmp);
            //             if(newP.x == 7) {
            //                 //King k(isWhite(), newP, board);
            //                 //std::vector<Move> king_move;
            //                 //king_move = k.getValidMoves;
            //                 //merge kazdy obiekt z king_move z current move i moves.push_back(kazdy ten nowy move);
            //                 continue;
            //             }
            //             Pawn p(isWhite(), newP, board);
            //             p.getCaptureMoves(moves, board, current);
            //         }
            //     }
            // }
            // else{
            //     if(board.getBoard()[pos.x][pos.y] == WhitePawn || board.getBoard()[pos.x][pos.y] == WhiteKing ){
            //         Position diff = positionDistance(pos);
            //         Position newP = Position(pos.x + diff.x, pos.y + diff.y);
            //         if (board.getBoard()[newP.x][newP.y] == Empty){
            //             countMoves++;
            //             Move tmp = Move(pos_, newP, pos);
            //             current.addStepMove(tmp);
            //             board.makeMove(tmp);
            //             Pawn p(isWhite(), newP, board);
            //             p.getCaptureMoves(moves, board, current);
            //         }
            //     }
            // }
        }
        
    }

    // if(countMoves == 0){
    //     return false;
    // }
    // return true;
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

    //TODO: nulle, czy dziala ok? sprawdza poza plansza -> do zmiany, drukowanie ruchow, testy, zamiana pionka na krolowa
    
}

void Pawn::canCapture(std::vector<Move> &moves, Board board, Move current) {};

std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}