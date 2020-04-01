#include <iostream>

#include "Pawn.hpp"
#include "Piece.hpp"
#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"

int main() {
    //Checkers ch = Checkers(true);

    bool isPlayerWhite = true;

    Board board = Board();

    Player user = Player(&board);
    user.setIsWhite(isPlayerWhite);
    Player computer = Player(&board);
    computer.setIsWhite(!isPlayerWhite);

    board.initialize(user, computer);
    
    Pawn* p1 = new Pawn(board.getSpotOnPosition(Position(1, 3)), false);
    Pawn* p2 = dynamic_cast<Pawn*>(board.getSpotOnPosition(Position(2, 2)).getPiece());
    std::cout << p2->canCapture(*p1) << std::endl;
    std::cout << p1->canCapture(*p2) << std::endl;


    //user.movePiece( user.getPlayerPiece, Position(2,4) ); //nie dziala :( 

    std::cout << board;

    //std::cout << ch.findTile("s") << std::endl;

    return 0;
}