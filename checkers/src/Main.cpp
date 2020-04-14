#include <iostream>

//#include "Pawn.hpp"
//#include "Piece.hpp"
//#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"

int main() {

    //Checkers ch = Checkers(true);

    Board board = Board();
    std::cout << "Drukuje tablice" << std::endl;
    std::cout << board << std::endl;
    std::cout << board.getFEN() << std::endl;


    Player user = Player(&board, true, true);
    user.initializePieces();

    std::cout << board << std::endl;
    std::cout << board.getFEN() << std::endl;


    Player computer = Player(&board, false, false);
    computer.initializePieces();

    std::cout << board << std::endl;
    
    std::cout << board.getFEN() << std::endl;

    user.printPlayer();
    std::cout << '\n' << std::endl;
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



    //std::cout << ch.findTile("s") << std::endl;

    return 0;
}