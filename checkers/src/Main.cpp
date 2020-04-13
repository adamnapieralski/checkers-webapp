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

    //std::cout << ch.findTile("s") << std::endl;

    Move m1(Position(1, 1), Position(3, 3), Position(2, 2));
    Move m2(Position(3, 3), Position(1, 5), Position(2, 4));
    auto m3 = m1.merge(m2);
    auto b2 = board;
    b2.makeMove(m3);
    std::cout << b2 << std::endl;

    return 0;
}