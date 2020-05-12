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
#include <map> 
#include <limits>
#include <algorithm>

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

double AIPlayer::evaluationFunction(AIPlayer computer, UserPlayer user, Board board){
    return 5.;
}

Move AIPlayer::minmax(AIPlayer computer, UserPlayer user, Board board) {
    std::vector<std::pair<Move, double>> heuristics;
    Board temp = board;
    AIPlayer temp_comp = computer;
    UserPlayer temp_user = user;
    double alpha = -std::numeric_limits<double>::infinity(); 
    double beta = std::numeric_limits<double>::infinity();

    for (auto& row : getValidMoves(board)){
        for (auto& mv : row){
            computer.movePiece(board, user, mv);
            heuristics.push_back(std::pair<Move,double>(mv, minmaxAlphaBeta(computer, user, board, 3, alpha, beta, true))); //chyba powinnismy przekazywac nowa alfe po kazdym zbadanym ruchu
            // heuristics.push_back(std::pair<Move, double>(mv, 2.));
            board = temp;
            computer = temp_comp;
            user = temp_user;

        }
    }
    auto max = std::max_element(heuristics.begin(),heuristics.end(),
        [] (const std::pair<Move,double>& a, const std::pair<Move,double>& b) {
            return a.second < b.second;
        }
    );
    
    std::cout << "Alpha:" << max->second << std::endl;

    return max->first;
}

double AIPlayer::minmaxAlphaBeta(AIPlayer computer, UserPlayer user, Board board, int depth, double alpha, double beta, bool isUser) {
    //end state
    std::vector<std::vector<Move>> valid_moves;
    if (depth == 0) return evaluationFunction(computer, user, board);
    if (isUser){
        if(computer.getPieces().size() == 0) return evaluationFunction(computer,user,board);
        valid_moves = user.getValidMoves(board);
    }
    else{
        if(user.getPieces().size() == 0) return evaluationFunction(computer,user,board);
        valid_moves = computer.getValidMoves(board);
    }
    if (valid_moves.size() == 0) return evaluationFunction(computer,user,board);

    Board temp = board;
    AIPlayer temp_comp = computer;
    UserPlayer temp_user = user;

    //max
    if(!isUser){
        for (auto& row : valid_moves){
            for (auto& mv : row){
                computer.movePiece(board, user, mv);
                alpha = std::max(alpha, minmaxAlphaBeta(computer,user,board, depth-1, alpha, beta, !isUser));
                if (alpha >= beta) return beta;
                board = temp;
                computer = temp_comp;
                user = temp_user;
            }
        }
        return alpha;
    }

    //min

    if(isUser){
        for (auto& row : valid_moves){
            for (auto& column : row){
                user.movePiece(board, user, column);
                beta = std::min(beta, minmaxAlphaBeta(computer,user,board, depth-1, alpha, beta, !isUser));
                if (alpha >= beta) return alpha;
                board = temp;
                computer = temp_comp;
                user = temp_user;
            }
        }
        return beta;
    }

    


    
    
    return 0.;
}

// GameTree AIPlayer::getGameTree(const UserPlayer &user, const Board &board) {
//     GameTree tree = GameTree(board);
//     AIPlayer computer = (*this); //konstruktor kopiujacy dla AIPlayer
//     fillTree(computer,user, tree, 0, board, false);    
//     return tree;
// }

// void AIPlayer::fillTree(AIPlayer computer,UserPlayer user, GameTree &tree, int depth, Board board, bool ifUser){
//     std::vector<std::vector<Move>> valid_moves;
//     Board temp = board;
//     AIPlayer temp_comp = computer;
//     UserPlayer temp_user = user;
//     if(depth == 3){
//         tree.changeCurrentHeadToParent();
//         return;
//     }

//     if (!ifUser){
//         valid_moves = computer.getValidMoves(board);
//         for (auto& row : valid_moves){
//             for (auto& column : row){
//                 computer.movePiece(board, user, column);
//                 tree.addChildren(column, board);
//                 fillTree(computer, user, tree, depth + 1, board, !ifUser);
//                 board = temp;
//                 computer = temp_comp;
//                 user = temp_user;
//             }
//         }
//     }
// }