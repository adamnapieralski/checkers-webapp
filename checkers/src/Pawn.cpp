#include "Pawn.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include <vector>

void Pawn::getCaptureMoves(std::vector<Move> &moves, Board board, Move current) {

    int dx[4] = {1,1,-1,-1};
    int dy[4] = {-1,1,-1,1};

    int countMoves = 0;
    for(int i = 0; i <4; ++i){
        Position pos(pos_.x + dx[i], pos_.y + dy[i]);
        if (pos.x >=0 && pos.y>= 0) {
            if (isWhite()){
                if(board.getBoard()[pos.x][pos.y] == BlackPawn || board.getBoard()[pos.x][pos.y] == BlackKing ){
                    Position diff = positionDistance(pos);
                    Position newP = Position(pos.x + diff.x, pos.y + diff.y);
                    if (board.getBoard()[newP.x][newP.y] == Empty){
                        countMoves++;
                        Move tmp = Move(pos_, newP, pos);
                        current.addStepMove(tmp);
                        board.makeMove(tmp);
                        if(newP.x == 7) {
                            //King k(isWhite(), newP, board);
                            //std::vector<Move> king_move;
                            //king_move = k.getValidMoves;
                            //merge kazdy obiekt z king_move z current move i moves.push_back(kazdy ten nowy move);
                            continue;
                        }
                        Pawn p(isWhite(), newP, board);
                        p.getCaptureMoves(moves, board, current);
                    }
                }
            }
            else{
                if(board.getBoard()[pos.x][pos.y] == WhitePawn || board.getBoard()[pos.x][pos.y] == WhiteKing ){
                    Position diff = positionDistance(pos);
                    Position newP = Position(pos.x + diff.x, pos.y + diff.y);
                    if (board.getBoard()[newP.x][newP.y] == Empty){
                        countMoves++;
                        Move tmp = Move(pos_, newP, pos);
                        current.addStepMove(tmp);
                        board.makeMove(tmp);
                        Pawn p(isWhite(), newP, board);
                        p.getCaptureMoves(moves, board, current);
                    }
                }
            }
        }
        
    }

    if(countMoves == 0){
        moves.push_back(current);
    }

    /*if (this->isWhite() == piece.isWhite()) return false;

    Position diff = positionDistance(piece);
    if (abs(diff.x) != 1 || abs(diff.y) != 1) return false;

    int newX = piece.getPosition().x + diff.x;
    int newY = piece.getPosition().y + diff.y;
    Position newPos(newX, newY);

    if (!newPos.isPositionValid()) return false;
    if (board.getBoard()[newX][newY] == Empty) return true;
    else return false;*/


}

std::vector<Move> Pawn::getValidMoves(Board &board, bool &mustCapture) {

    std::vector<Move> moves;
    Move move;

    mustCapture = true;
    getCaptureMoves(moves, board, move);

    if (moves.size() == 1 && moves[0] == move){
        int d[2] ={1, -1};
        moves.pop_back();
        if (this->isWhite() ) {
            for(int i = 0 ; i < 2 ; ++i){
                if(board.getBoard()[pos_.x + 1][pos_.y + d[i]] == Empty){
                    moves.push_back(Move(pos_,Position(pos_.x + 1, pos_.y +d[i])));
                }
            }
        }
        else {
            for(int i = 0 ; i < 2 ; ++i){
                if(board.getBoard()[pos_.x - 1][pos_.y + d[i]] == Empty){
                    moves.push_back(Move(pos_,Position(pos_.x - 1, pos_.y +d[i])));
                }
            }
        }
        mustCapture = false;
    }

    return moves;

    //TODO: nulle, czy dziala ok? sprawdza poza plansza -> do zmiany, drukowanie ruchow, testy, zamiana pionka na krolowa
    
}

void Pawn::canCapture(std::vector<Move> &moves, Board board, Move current){};

std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}