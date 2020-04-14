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


    std::vector<Move> valid_moves;
    valid_moves = user.getValidMoves(board);
    if(valid_moves.size() != 0 )
        board.makeMove(valid_moves[1]);
    std::cout << board << std::endl;

    //std::cout << ch.findTile("s") << std::endl;

    return 0;
}