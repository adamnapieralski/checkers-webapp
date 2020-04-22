#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CheckersTests
#include <boost/test/unit_test.hpp>

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

    BOOST_CHECK(moves.size() == 11);

    user.movePiece(board, computer, moves[0]);

    std::vector<Piece*> newComp = computer.getPieces();
    std::vector<Piece*> newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 1);
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(0,0);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WhiteKing);

}

BOOST_AUTO_TEST_CASE( move_merge )
{
    // two simple
    Move mSimp1(Position(0, 0), Position(1, 1));
    Move mSimp2(Position(1, 1), Position(0, 2));
    auto merge1 = mSimp1.merge(mSimp2);
    
    BOOST_CHECK( merge1.getStartPosition() == Position(0, 0) );
    BOOST_CHECK( merge1.getEndPosition() == Position(0, 2) );
    BOOST_CHECK( merge1.getStepMoves().size() == 2 );

    BOOST_REQUIRE_THROW( mSimp2.merge(mSimp1), std::out_of_range );

    // complex + simple
    Move mComp1(Position(0, 2), Position(2, 4), Position(1, 3) );
    auto merge2 = mSimp2.merge(mComp1);
    BOOST_CHECK( merge2.getCapturedPositions().size() == 1 && merge2.getCapturedPositions()[0] == Position(1, 3) );
    BOOST_CHECK( merge2.getStepMoves().size() == 2 );

    // two complex
    Move mComp2(Position(2, 4), Position(4, 2), Position(3, 3) );
    auto merge3 = mComp1.merge(mComp2);
    BOOST_CHECK( merge3.getCapturedPositions().size() == 2 );
    Move mComp3(Position(4, 2), Position(6, 4), Position(5, 3));
    auto merge4 = merge3.merge(mComp3);
    BOOST_CHECK( merge4.getStartPosition() == Position(0, 2) && merge4.getEndPosition() == Position(6, 4) );
    BOOST_CHECK( merge4.getStepMoves().size() == 3 );
    
}

BOOST_AUTO_TEST_CASE( board_fen )
{
    Board board = Board();
    Player user = Player(&board, true, true);
    Player computer = Player(&board, false, false);
    user.initializePieces();
    computer.initializePieces();
    BOOST_CHECK( board.getFEN() == "1P1P1P1P/P1P1P1P1/1P1P1P1P/8/8/p1p1p1p1/1p1p1p1p/p1p1p1p1" );

    board.placePiece(Position(0, 0), WhiteKing);
    board.placePiece(Position(4, 4), BlackKing);
    board.placePiece(Position(2, 6), WhiteKing);
    board.placePiece(Position(7, 7), BlackKing);
    board.placePiece(Position(5, 3), WhiteKing);
    BOOST_CHECK( board.getFEN() == "1P1P1P1K/P1k1P1P1/1P1P1P1P/4K3/5k2/p1p1p1p1/1p1p1p1p/k1p1p1p1" );
}


BOOST_AUTO_TEST_SUITE_END()