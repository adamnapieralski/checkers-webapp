#include <iostream>

#include "Pawn.hpp"
#include "Checkers.hpp"
#include "Player.hpp"
#include "Board.hpp"

int main() {
    Checkers ch = Checkers(true);

    bool isPlayerWhite = true;

    Player user = Player();
    user.setIsWhite(isPlayerWhite);
    Player computer = Player();
    computer.setIsWhite(!isPlayerWhite);

    Board board = Board();

    board.initialize(user, computer);

    std::cout << board;

    std::cout << ch.findTile("s") << std::endl;

    return 0;
}