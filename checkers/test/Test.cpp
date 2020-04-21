#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>


#include "../src/Player.hpp"
#include "../src/Board.hpp"
#include "../src/King.hpp"
#include "../src/Pawn.hpp"


BOOST_AUTO_TEST_SUITE(MovePiece)

BOOST_AUTO_TEST_CASE( changePawKing ) //change Pawn to King
{   

    Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    user.addPiece(false, Position(1, 5),board);
    computer.addPiece(true, Position(2,6), board);
    computer.addPiece(false, Position(5,5), board);

    auto moves = user.getValidMovePiece(board, 0);

    BOOST_CHECK(moves.size() == 2);

    user.movePiece(board, computer, moves[0]);
    std::vector<Piece*> newComp = computer.getPieces();
    std::vector<Piece*> newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 0);
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(6,4);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WhiteKing);

}

BOOST_AUTO_TEST_CASE( pawn ) //check Pawn
{   

    Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    user.addPiece(false, Position(2, 2),board);
    computer.addPiece(false, Position(3,3), board);
    computer.addPiece(false, Position(1,1), board);
    computer.addPiece(false, Position(5,3), board);
    auto moves = user.getValidMovePiece(board, 0);

    BOOST_CHECK(moves.size() == 2);

    user.movePiece(board, computer, moves[1]);

    std::vector<Piece*> newComp = computer.getPieces();
    std::vector<Piece*> newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 1 || newComp.size() == 2 );
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(0,0);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WhitePawn);

}


BOOST_AUTO_TEST_CASE( king ) //check King
{   

    Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    user.addPiece(true, Position(2, 2),board);
    computer.addPiece(false, Position(3,3), board);
    computer.addPiece(false, Position(1,1), board);
    computer.addPiece(false, Position(5,3), board);
    auto moves = user.getValidMovePiece(board, 0);

    BOOST_CHECK(moves.size() == 2);

    user.movePiece(board, computer, moves[1]);

    std::vector<Piece*> newComp = computer.getPieces();
    std::vector<Piece*> newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 1 || newComp.size() == 2 );
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(0,0);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WhiteKing);

}


BOOST_AUTO_TEST_SUITE_END()