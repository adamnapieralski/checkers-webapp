#include <iostream>

#include "Checkers.h"
#include "AIPlayer.h"
#include "UserPlayer.h"
#include "Board.h"
#include "King.h"
#include "Pawn.h"
#include "GameTree.h"

int main() {
 
    Board board = Board();
    auto user = UserPlayer(true);
    auto computer = AIPlayer(false);
    computer.addPiece(true, Position(2, 2), board);
    computer.addPiece(false, Position(4, 4), board);
    // computer.addPiece(true, Position(3, 0), board);
    // user.addPiece(false, Position(3,3), board);
    user.addPiece(false, Position(1,1), board);
    user.addPiece(false, Position(5,3), board);
    // user.addPiece(false, Position(3,3), board);
    std::cout << board.getFEN() << std::endl;


    auto userPieces = user.getPieces();
    auto p1 = userPieces[0];
    auto p2 = p1->clone();

    // std::cout << board << std::endl;
    // Move t = computer.minmax(computer, user, board);
    // computer.movePiece(board, user, t);
    // std::cout << board << std::endl;
    /* std::vector<Piece*> newComp = computer.getPieces();
    std::vector<Piece*> newUs = user.getPieces();*/

    auto checkers = Checkers::getInstance();
    // checkers.initialize("Adam", true);
    // std::cout << checkers.getBoard() << std::endl;

    // checkers.makeComputerMove();
    // checkers.processUserMove("c3", "d4");
    // std::cout << checkers.getBoard() << std::endl;
    // checkers.makeComputerMove();
    // std::cout << checkers.getBoard() << std::endl;
    // checkers.processUserMove("d4", "e5");
    // checkers.processUserMove("d2", "c3");
    // checkers.makeComputerMove();
    // checkers.processUserMove("c3", "b4");
    // checkers.makeComputerMove();
    // checkers.processUserMove("b2", "c3");   
    // checkers.processUserMove("c3", "d4");
    std::cout << checkers.getBoard() << std::endl;

    // std::string fen = "8/3P4/8/4p3/5P2/2k5/1P6/8";
    // checkers.fenInitialize(fen, "Adam", true, true);
    // std::cout << checkers.getBoard() << std::endl;
    // checkers.processUserMove("b2", "d4");


    auto ch = Checkers::getInstance();
    ch.fenInitialize("8/4P3/1p6/8/8/8/8/8", "Willy Wonka", true, true);
    auto state = ch.processUserMove("e7", "d8");
    std::cout << ch.getBoard() << std::endl;
    state = ch.processUserMove("d8", "a5");
    std::cout << ch.getBoard() << std::endl;


    return 0;
}