/**
 * @file AIPlayer.cc
 * @brief Source file for AI class, representing AI player.
 * 
 * @author Adam Napieralski
 * @author Patrycja Cieplicka
 */

#include "AIPlayer.h"
#include "Pawn.h"
#include "King.h"
#include "GameTree.h"

AIPlayer::AIPlayer(bool isWhite) : Player(isWhite) {
    name_ = "Computer";
}

void AIPlayer::initializePieces(Board& board){
    for (int i = BOARD_SIZE - 1; i > INIT_ROW + 1; --i){
        for (int j = 0; j < BOARD_SIZE; ++j){
            if ((i + j) % 2 == 0){
                pieces_.push_back(std::make_shared<Pawn>(Position(j, i), isWhite_, false, board));
            }
        }
    }
}

void AIPlayer::addPiece(bool isKing, Position pos, Board& board){
    if(isKing) pieces_.push_back(std::make_shared<King>(pos, isWhite_, false, board));
    else pieces_.push_back(std::make_shared<Pawn>(pos, isWhite_, false, board));
}

Move AIPlayer::minmax() {
    return Move();
}

double AIPlayer::minmaxAlphaBeta() {
    return 0.;
}

GameTree AIPlayer::getGameTree(const UserPlayer &user, const Board &board) {
    GameTree tree = GameTree(board);
    AIPlayer computer = (*this); //konstruktor kopiujacy dla AIPlayer
    fillTree(computer,user, tree, 0, board, false);    
    return tree;
}

void AIPlayer::fillTree(AIPlayer computer,UserPlayer user, GameTree &tree, int depth, Board board, bool ifUser){
    std::vector<std::vector<Move>> valid_moves;
    Board temp = board;
    AIPlayer temp_comp = computer;
    UserPlayer temp_user = user;
    if(depth == 3){
        tree.changeCurrentHeadToParent();
        return;
    }

    if (!ifUser){
        valid_moves = computer.getValidMoves(board);
        for (auto& row : valid_moves){
            for (auto& column : row){
                computer.movePiece(board, user, column);
                tree.addChildren(column, board);
                fillTree(computer, user, tree, depth + 1, board, !ifUser);
                board = temp;
                computer = temp_comp;
                user = temp_user;
            }
        }
    }
}