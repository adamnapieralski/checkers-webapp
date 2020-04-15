#include <iostream>

//#include "Pawn.hpp"
//#include "Piece.hpp"
//#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "King.hpp"
#include "Pawn.hpp"

int main() {

    //Checkers ch = Checkers(true);

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


    std::vector<Move> valid_moves;
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
    std::cout << board << std::endl;


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

    return 0;
}