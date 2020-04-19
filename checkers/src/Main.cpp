#include <iostream>

//#include "Pawn.hpp"
//#include "Piece.hpp"
//#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Pawn.hpp"

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

    
    Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    computer.addPiece(false, Position(2, 2),board);
    user.addPiece(false, Position(3,3), board);
    user.addPiece(false, Position(1,1), board);
    user.addPiece(false, Position(5,3), board);
    std::cout << board << std::endl;
    auto moves = computer.getValidMovePiece(board, 0);


    computer.movePiece(board, user, moves[0]);
    std::cout << board << std::endl;
    //std::vector<Piece*> newComp = computer.getPieces();
    //std::vector<Piece*> newUs = user.getPieces();


    return 0;
}