#include <iostream>

#include "Pawn.hpp"
#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"

int main() {
    Checkers ch = Checkers(true);

    Player user = Player();
    user.setIsWhite(true);
    Player computer = Player();
    computer.setIsWhite(false);

    Board board = Board();

    board.initialize(user, computer);

    std::cout << ch.findTile("s") << std::endl;

    return 0;
}