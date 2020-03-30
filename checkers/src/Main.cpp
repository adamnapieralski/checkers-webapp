#include <iostream>

#include "Pawn.h"
#include "Checkers.h"
#include "Player.h"
#include "Board.h"

int main() {
    Checkers ch = Checkers();

    Player user = Player();
    user.setIsWhite(true);
    Player computer = Player();
    computer.setIsWhite(false);

    Board board = Board();

    board.initialize(user, computer);

    std::cout << ch.findTile("s") << std::endl;

    return 0;
}