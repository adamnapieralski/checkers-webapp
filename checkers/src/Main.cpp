#include <iostream>

//#include "Pawn.hpp"
//#include "Piece.hpp"
//#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Pawn.hpp"

int main() {
    Board board = Board();
    std::cout << "Drukuje tablice" << std::endl;
    std::cout << board << std::endl;
    std::cout << board.getFEN() << std::endl;


    Player user = Player(&board, true, true);
    user.initializePieces();

    std::cout << "User" << std::endl << board << std::endl;
    std::cout << board.getFEN() << std::endl;


    Player computer = Player(&board, false, false);
    computer.initializePieces();

    std::cout << "User+Comp" << std::endl << board << std::endl << board.getFEN() << std::endl;
    
    auto initBoard = board;

    user.printPlayer();
    std::cout << std::endl << std::endl;
    computer.printPlayer();


   /* std::vector<Move> valid_moves;
    std::vector<Move> valid_comp;
    valid_moves = user.getValidMoves(board, 10);
    if(valid_moves.size() != 0 ){
        user.movePiece(board,10,valid_moves[1]);
    }
    std::cout << board << std::endl;

    valid_comp = computer.getValidMoves(board, 10);
    if(valid_comp.size() != 0 ){
        computer.movePiece(board,10,valid_comp[1]);
    }
    std::cout << board << std::endl;
    

    valid_moves = user.getValidMoves(board, 10);
    std::cout << valid_moves.size() << std::endl;
    if(valid_moves.size() != 0 ){
        user.movePiece(board,10,valid_moves[0]);
    }
    std::cout << board << std::endl;
    
    Move tmp = Move(Position(2,2), Position(3,3));
    board.makeMove(tmp);

    std::cout << board << std::endl;

    valid_moves = computer.getValidMoves(board, 7);
    std::cout << valid_moves.size() << std::endl;
    if(valid_moves.size() != 0 ){
        computer.movePiece(board,7,valid_moves[0]);
    }
    std::cout << board << std::endl;*/


    std::cout << "King test" << std::endl;
    std::cout << initBoard << std::endl;
    Move m1(Position(1, 1), Position(3, 3), Position(2, 2));
    Move m2(Position(3, 3), Position(1, 5), Position(2, 4));
    auto m3 = m1.merge(m2);
    auto b2 = initBoard;
    b2.makeMove(m3);
    std::cout << b2 << std::endl;
    King k(Position(3, 3), false, false, b2);
    Pawn p(Position(1, 1), true, true, b2);
    b2.clearPosition(Position(5, 1));
    b2.clearPosition(Position(0, 0));

    std::cout << b2 << std::endl;
    auto mv = k.getValidMoves(b2);
    b2.makeMove(mv[1]);
    std::cout << b2 << std::endl;

    //Pawn test
    std::cout << "Pawn test" << std::endl;
    std::cout << initBoard << std::endl;
    Move m4(Position(1, 1), Position(3, 3), Position(2, 2));
    Move m5(Position(3, 3), Position(1, 5), Position(2, 4));
    auto m6 = m4.merge(m5);
    auto b3 = initBoard;
    b3.makeMove(m6);
    std::cout << b3 << std::endl;
    Pawn l(Position(3, 3), false, false, b3);
    Pawn m(Position(1, 1), true, true, b3);
    b3.clearPosition(Position(5, 1));
    b3.clearPosition(Position(0, 0));

    std::cout << b3 << std::endl;
    auto mve = l.getValidMoves(b3);
    b3.makeMove(mve[0]);
    std::cout << b3 << std::endl;


    // test for pawn to king change
    std::cout << "Test: Pawn to King change" << std::endl;
    Board newBoard = Board();
    auto pawnW1 = Pawn(Position(1, 5), true, true, newBoard);
    auto kingB1 = King(Position(2, 6), false, false, newBoard);
    auto pawnB1 = Pawn(Position(5, 5), false, false, newBoard);
    std::cout << newBoard << std::endl;
    auto mvs = pawnW1.getValidMoves(newBoard);
    newBoard.makeMove(mvs[0]);
    std::cout << newBoard << std::endl;
    // TODO: change piece from pawn to king

    return 0;
}