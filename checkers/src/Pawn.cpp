#include "Pawn.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include <vector>

void Pawn::canCapture(std::vector<Move> &moves, Board board, Move current) {

    int countMoves = 0;
    for (int i = pos_.x - 1; i <= pos_.x + 1; i = i + 2){
        for (int j = pos_.y - 1; j <= pos_.y + 1; j = j + 2){
            if (i >=0 && j>= 0) {
                if (isWhite()){
                    if(board.getBoard()[i][j] == BlackPawn || board.getBoard()[i][j] == BlackKing ){
                        Position diff = positionDistance(Position(i,j));
                        Position newP = Position(i + diff.x, j + diff.y);
                        if (board.getBoard()[newP.x][newP.y] == Empty){
                            countMoves++;
                            Move tmp = Move(pos_, newP, Position(i,j));
                            current.addStepMove(tmp);
                            canCapture(moves, board, current);
                        }
                    }
                }
                else{
                    if(board.getBoard()[i][j] == WhitePawn || board.getBoard()[i][j] == WhiteKing ){
                        Position diff = positionDistance(Position(i,j));
                        Position newP = Position(i + diff.x, j + diff.y);
                        if (board.getBoard()[newP.x][newP.y] == Empty){
                            countMoves++;
                            Move tmp = Move(pos_, newP, Position(i,j));
                            current.addStepMove(tmp);
                            canCapture(moves, board, current);
                        }
                    }
                }
            }
        }
    }

    if(countMoves = 0){
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

std::vector<Move> Pawn::getValidMoves(Board &board) {

    std::vector<Move> moves;
    Move move;

    canCapture(moves, board, move);

    if (moves.size() == 1 && moves[0] == move){
        if (this->isWhite() ) {
            if(board.getBoard()[pos_.x + 1][pos_.y + 1] == Empty){
                moves.push_back(Move(pos_,Position(pos_.x + 1, pos_.y +1)));
            }
            if(board.getBoard()[pos_.x + 1][pos_.y - 1] == Empty){
                moves.push_back(Move(pos_,Position(pos_.x + 1, pos_.y -1)));
            }
        }
        else {
            if(board.getBoard()[pos_.x - 1][pos_.y - 1] == Empty){
                moves.push_back(Move(pos_,Position(pos_.x - 1, pos_.y -1)));
            }
            if(board.getBoard()[pos_.x - 1][pos_.y + 1] == Empty){
                moves.push_back(Move(pos_,Position(pos_.x - 1, pos_.y +1)));
            }
        }

    }

    if (moves.size() == 1 && moves[0] == move){
        moves.pop_back();
    }
    return moves;

    //TODO: nulle, czy dziala ok? sprawdza poza plansza -> do zmiany, drukowanie ruchow, testy
    
}


std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}