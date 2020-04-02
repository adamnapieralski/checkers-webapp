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

    Player user = Player(&board, true);
    user.initializePieces();

    std::cout << board << std::endl;

    Player computer = Player(&board, false);
    computer.initializePieces();

    std::cout << board << std::endl;


    /*bool isPlayerWhite = true;

    Board board = Board();

    Player user = Player();
    user.setIsWhite(isPlayerWhite);
    Player computer = Player();
    computer.setIsWhite(!isPlayerWhite);*/
    

    //std::cout << ch.findTile("s") << std::endl;

    return 0;
}