#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>
#include "../src/Player.hpp"
#include "../src/Board.hpp"
#include "../src/King.hpp"
#include "../src/Pawn.hpp"



BOOST_AUTO_TEST_CASE( test1 ) //change Pawn to King
{
    Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    user.addPiece(false, Position(1, 5),board);
    computer.addPiece(true, Position(2,6), board);
    computer.addPiece(false, Position(5,5), board);
    std::cout << board << std::endl;

    

}