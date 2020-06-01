/**
 * @file Pawn.cc
 * @brief Source file for Pawn class, representing pawn piece.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#include "Pawn.h"
#include "Board.h"
#include "Move.h"
#include "King.h"
#include <vector>

Pawn::Pawn(Position pos, bool isWhite, bool isUser, Board& board) : Piece(pos, isWhite, isUser) {
    if (isWhite)
        board.placePiece(pos, WHITE_PAWN);
    else
        board.placePiece(pos, BLACK_PAWN);
}

/*std::shared_ptr<Pawn> Pawn::clone() const {
    return std::static_pointer_cast<Pawn>(cloneImplementation());
}*/

std::shared_ptr<Piece> Pawn::cloneImplementation() const {
    return std::shared_ptr<Pawn>(new Pawn(*this));
}

void Pawn::captureMoves(std::vector<Move>& moves, Board board, Move current) const {
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
                if (newPos.isValid() && board.getPieceName(newPos) == EMPTY) {
                    ++countMoves;
                    Move tmp = Move(startPos, newPos, capPos);

                    if (current.isInitial()) current = tmp;
                    else current = current.merge(tmp);
                    board.makeMove(tmp);
                    if (newPos.isLastRow(isUser())) {
                        current.addUpgradePosition(newPos);
                        King k(newPos, isWhite(), isUser(), board);
                        k.captureMoves(moves, board, current);
                        current = tmpCurrent;
                        board = tmpBoard;
                        continue;
                    }
                    Pawn p(newPos, isWhite(), isUser(), board);
                    p.captureMoves(moves, board, current);
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

std::vector<Move> Pawn::getCaptureMoves(Board& board) const{
    std::vector<Move> moves;
    Move move;

    captureMoves(moves, board, move);

    return moves;
}

std::vector<Move> Pawn::getNonCaptureMoves(Board& board) const{

    std::vector<Move> moves;

    int d[2] ={1, -1};
    if (isUser()) {
        for(int i = 0 ; i < 2 ; ++i){
            Position nP(getPosition().x + d[i], getPosition().y + 1);
            if(nP.isValid() && board.getPieceName(nP) == EMPTY){
                Move tmp = Move(getPosition(), nP);
                if (nP.isLastRow(isUser())) {
                       tmp.addUpgradePosition(nP);
                    }
                moves.push_back(tmp);
            }
        }
    }
    else {
        for(int i = 0 ; i < 2 ; ++i){
            Position nP(getPosition().x + d[i], getPosition().y - 1);
            if(nP.isValid() && board.getPieceName(nP) == EMPTY){
                Move tmp = Move(getPosition(), nP);
                if (nP.isLastRow(isUser())) {
                       tmp.addUpgradePosition(nP);
                    }
                moves.push_back(tmp);
            }
        }
    }

    return moves;
}

std::ostream& Pawn::print(std::ostream& os) const{
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}