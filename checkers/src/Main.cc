#include <iostream>

//#include "Pawn.hpp"
//#include "Piece.hpp"
//#include "Checkers.hpp"
#include "AIPlayer.h"
#include "UserPlayer.h"
#include "Board.h"
#include "King.h"
#include "Pawn.h"
#include "GameTree.h"

int main() {
    /*Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    user.addPiece(false, Position(1, 5),board);
    computer.addPiece(true, Position(2,6), board);
    computer.addPiece(false, Position(5,5), board);
    std::cout << board << std::endl;
    auto moves = user.getValidMovePiece(board, 0);
    user.movePiece(board, computer, moves[0]);
    std::cout << board << std::endl;*/

    
    /*Board board = Board();
    auto user = UserPlayer(true);
    auto computer = AIPlayer(false);
    computer.addPiece(true, Position(2, 2), board);
    // computer.addPiece(true, Position(3, 0), board);
    user.addPiece(false, Position(3,3), board);
    user.addPiece(false, Position(1,1), board);
    user.addPiece(false, Position(5,3), board);
    std::cout << board << std::endl;
    auto moves = computer.getValidMoves(board);
    // auto movesK = computer.getValidMovePiece(board, 1);

    computer.movePiece(board, user, moves[0][0]);
    std::cout << board << std::endl;
    //std::vector<Piece*> newComp = computer.getPieces();
    //std::vector<Piece*> newUs = user.getPieces();*/

    GameTree tree = GameTree();

    return 0;
}