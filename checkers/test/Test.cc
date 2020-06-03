/**
 * @file Test.cc
 * @brief Source file for unit tests using Boost.Test.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CheckersTests
#include <boost/test/unit_test.hpp>

#include "../src/Checkers.h"
#include "../src/UserPlayer.h"
#include "../src/AIPlayer.h"
#include "../src/Board.h"
#include "../src/King.h"
#include "../src/Pawn.h"


BOOST_AUTO_TEST_SUITE(MovePiece)


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
    auto user = UserPlayer(true);
    auto computer = AIPlayer(false);
    user.initializePieces(board);
    computer.initializePieces(board);
    BOOST_CHECK( board.getFEN() == "1p1p1p1p/p1p1p1p1/1p1p1p1p/8/8/P1P1P1P1/1P1P1P1P/P1P1P1P1" );

    board.placePiece(Position(0, 0), WHITE_KING);
    board.placePiece(Position(4, 4), BLACK_KING);
    board.placePiece(Position(2, 6), WHITE_KING);
    board.placePiece(Position(7, 7), BLACK_KING);
    board.placePiece(Position(5, 3), WHITE_KING);
    BOOST_CHECK( board.getFEN() == "1p1p1p1k/p1K1p1p1/1p1p1p1p/4k3/5K2/P1P1P1P1/1P1P1P1P/K1P1P1P1" );
}

BOOST_AUTO_TEST_CASE( board_make_move )
{
    Board board = Board();
    board.placePiece(Position(1, 1), WHITE_KING);
    board.placePiece(Position(2, 2), BLACK_PAWN);
    board.placePiece(Position(4, 2), BLACK_PAWN);
    Move m1(Position(1, 1), Position(3, 3), Position(2, 2));
    Move m2(Position(3, 3), Position(5, 1), Position(4, 2));
    auto mv = m1.merge(m2);
    board.makeMove(mv);

    BOOST_CHECK( board.getPieceName(Position(1, 1)) == EMPTY );
    BOOST_CHECK( board.getPieceName(Position(2, 2)) == EMPTY );
    BOOST_CHECK( board.getPieceName(Position(4, 2)) == EMPTY );
    BOOST_CHECK( board.getPieceName(Position(5, 1)) == WHITE_KING );
}


BOOST_AUTO_TEST_CASE( capture_moves_pawn_simple ){
    //empty case
    Board board = Board();
    Pawn player_a(Position(1,5), true, true, board);
    std::vector<Move> moves_a;
    moves_a = player_a.getCaptureMoves(board);

    BOOST_REQUIRE(moves_a.empty());

    //simple case
    Pawn player_b(Position(2,6), false, false, board);
    std::vector<Move> moves_b;
    moves_b = player_b.getCaptureMoves(board);
    moves_a = player_a.getCaptureMoves(board);

    BOOST_REQUIRE(moves_a.size() == 1);
    BOOST_REQUIRE(moves_b.size() == 1);

    Move move_a = moves_a[0];

    BOOST_CHECK( move_a.getStartPosition() == Position(1,5) );
    BOOST_CHECK( move_a.getEndPosition() == Position(3,7));
    BOOST_REQUIRE( move_a.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_a.getCapturedPositions()[0] == Position(2,6));
    BOOST_CHECK( move_a.getStepMoves().empty());
    BOOST_REQUIRE( move_a.getUpgradePositions().size() == 1 );
    BOOST_CHECK (move_a.getUpgradePositions()[0] == Position(3,7));

    Move move_b = moves_b[0];

    BOOST_CHECK( move_b.getStartPosition() == Position(2,6) );
    BOOST_CHECK( move_b.getEndPosition() == Position(0,4));
    BOOST_REQUIRE( move_b.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_b.getCapturedPositions()[0] == Position(1,5));
    BOOST_CHECK( move_b.getStepMoves().empty());
    BOOST_CHECK( move_b.getUpgradePositions().empty());

    
}

BOOST_AUTO_TEST_CASE( capture_moves_king_simple ){
    //empty case
    Board board = Board();
    King player_a(Position(1,4), true, true, board);
    std::vector<Move> moves_a;
    moves_a = player_a.getCaptureMoves(board);

    BOOST_REQUIRE(moves_a.empty());

    //simple case
    King player_b(Position(2,5), false, false, board);
    std::vector<Move> moves_b;
    moves_b = player_b.getCaptureMoves(board);
    moves_a = player_a.getCaptureMoves(board);

    BOOST_REQUIRE(moves_a.size() == 2);
    BOOST_REQUIRE(moves_b.size() == 1);

    Move move_a = moves_a[1];

    BOOST_CHECK( move_a.getStartPosition() == Position(1,4) );
    BOOST_CHECK( move_a.getEndPosition() == Position(4,7));
    BOOST_REQUIRE( move_a.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_a.getCapturedPositions()[0] == Position(2,5));
    BOOST_CHECK( move_a.getStepMoves().empty());
    BOOST_CHECK( move_a.getUpgradePositions().empty() );

    Move move_b = moves_b[0];

    BOOST_CHECK( move_b.getStartPosition() == Position(2,5) );
    BOOST_CHECK( move_b.getEndPosition() == Position(0,3));
    BOOST_REQUIRE( move_b.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_b.getCapturedPositions()[0] == Position(1,4));
    BOOST_CHECK( move_b.getStepMoves().empty());
    BOOST_CHECK( move_b.getUpgradePositions().empty());

    
}

BOOST_AUTO_TEST_CASE ( capture_moves_pawn ){
    //More complicated test
    Board board = Board();

    Pawn player_a_1( Position(1,1), false, false, board);
    Pawn player_a_2( Position(3,3), false, false, board);
    Pawn player_a_3( Position(5,3), false, false, board);

    Pawn player_b(Position(2,2), true, true, board);

    std::vector<Move> moves_b = player_b.getCaptureMoves(board);

    BOOST_REQUIRE(moves_b.size() == 2);
    
    Move move_b_0 = moves_b[0];

    BOOST_CHECK( move_b_0.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_0.getEndPosition() == Position(6,2));
    BOOST_REQUIRE( move_b_0.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_0.getCapturedPositions()[0] == Position(3,3) && move_b_0.getCapturedPositions()[1] == Position(5,3));
    BOOST_CHECK( move_b_0.getStepMoves().size() == 2 );
    BOOST_CHECK( move_b_0.getUpgradePositions().empty());

    Move move_b_1 = moves_b[1];

    BOOST_CHECK( move_b_1.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_1.getEndPosition() == Position(0,0));
    BOOST_REQUIRE( move_b_1.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_b_1.getCapturedPositions()[0] == Position(1,1) );
    BOOST_CHECK( move_b_1.getStepMoves().empty() );
    BOOST_CHECK( move_b_1.getUpgradePositions().empty());

    std::vector<Move> moves_a_1 = player_a_1.getCaptureMoves(board);
    std::vector<Move> moves_a_2 = player_a_2.getCaptureMoves(board);
    std::vector<Move> moves_a_3 = player_a_3.getCaptureMoves(board);

    BOOST_CHECK( moves_a_1.empty() && moves_a_2.empty() && moves_a_3.empty() );

}

BOOST_AUTO_TEST_CASE ( capture_moves_king ){
    //More complicated test
    Board board = Board();

    Pawn player_a_1( Position(1,1), true, true, board);
    Pawn player_a_2( Position(3,3), true, true, board);
    Pawn player_a_3( Position(5,3), true, true, board);

    King player_b(Position(2,2), false, false, board);
    Pawn player_b_1(Position(3,1), false, false, board);

    std::vector<Move> moves_b = player_b.getCaptureMoves(board);

    BOOST_REQUIRE(moves_b.size() == 11);
    
    Move move_b_0 = moves_b[0];

    BOOST_CHECK( move_b_0.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_0.getEndPosition() == Position(0,0));
    BOOST_REQUIRE( move_b_0.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_0.getCapturedPositions()[0] == Position(3,3) && move_b_0.getCapturedPositions()[1] == Position(1,1) );
    BOOST_CHECK( move_b_0.getStepMoves().size() == 2 );
    BOOST_CHECK (move_b_0.getUpgradePositions().empty());

    Move step_b_0 =  move_b_0.getStepMoves()[0];
    BOOST_CHECK( step_b_0.getStartPosition() == Position(2,2) );
    BOOST_CHECK( step_b_0.getEndPosition() == Position(4,4));
    BOOST_REQUIRE( step_b_0.getCapturedPositions().size() == 1 );
    BOOST_CHECK( step_b_0.getCapturedPositions()[0] == Position(3,3) );
    BOOST_CHECK( step_b_0.getStepMoves().empty() );
    BOOST_CHECK (step_b_0.getUpgradePositions().empty());

    Move move_b_1 = moves_b[8];

    BOOST_CHECK( move_b_1.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_1.getEndPosition() == Position(5,5));
    BOOST_REQUIRE( move_b_1.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_1.getCapturedPositions()[0] == Position(1,1) &&  move_b_1.getCapturedPositions()[1] == Position(3,3));
    BOOST_CHECK( move_b_1.getStepMoves().size() == 2);
    BOOST_CHECK (move_b_0.getUpgradePositions().empty());


}

BOOST_AUTO_TEST_CASE ( capture_change_pawn_king ){
    //More complicated test
    Board board = Board();

    Pawn player_a_1( Position(1,1), true, true, board);
    Pawn player_a_2( Position(3,3), true, true, board);
    Pawn player_a_3( Position(5,3), true, true, board);

    Pawn player_b(Position(2,2), false, false, board);
    Pawn player_b_1(Position(3,1), false, false, board);

    std::vector<Move> moves_b = player_b.getCaptureMoves(board);

    BOOST_REQUIRE(moves_b.size() == 6);
    
    Move move_b_0 = moves_b[1];

    BOOST_CHECK( move_b_0.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_0.getEndPosition() == Position(6,2));
    BOOST_REQUIRE( move_b_0.getCapturedPositions().size() == 3 );
    BOOST_CHECK( move_b_0.getCapturedPositions()[0] == Position(1,1) && move_b_0.getCapturedPositions()[1] == Position(3,3) &&
                                         move_b_0.getCapturedPositions()[2] == Position(5,3));
    BOOST_CHECK( move_b_0.getStepMoves().size() == 3 );
    BOOST_REQUIRE( move_b_0.getUpgradePositions().size() == 1);
    BOOST_CHECK (move_b_0.getUpgradePositions()[0] == Position(0,0));

    Move move_b_1 = moves_b[4];

    BOOST_CHECK( move_b_1.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_1.getEndPosition() == Position(6,6));
    BOOST_REQUIRE( move_b_1.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_1.getCapturedPositions()[0] == Position(1,1) &&  move_b_1.getCapturedPositions()[1] == Position(3,3));
    BOOST_CHECK( move_b_1.getStepMoves().size() == 2);
    BOOST_REQUIRE( move_b_0.getUpgradePositions().size() == 1);
    BOOST_CHECK (move_b_0.getUpgradePositions()[0] == Position(0,0));

}

BOOST_AUTO_TEST_CASE(no_capture_moves_pawn){
    Board board = Board();
    Pawn p1(Position(1,1), true, true, board);
    Pawn p2(Position(0,0), true, true, board);
    Pawn p3(Position(2,2), true, true, board);
    Pawn p4(Position(7,1), false, false, board);

    std::vector<Move> moves_p1 = p1.getNonCaptureMoves(board);

    BOOST_REQUIRE (moves_p1.size() == 1);
    BOOST_CHECK( moves_p1[0].getStartPosition() == Position(1,1) );
    BOOST_CHECK( moves_p1[0].getEndPosition() == Position(0,2));
    BOOST_CHECK( moves_p1[0].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p1[0].getStepMoves().empty() );
    BOOST_CHECK( moves_p1[0].getUpgradePositions().empty() );

    std::vector<Move> moves_p2 = p2.getNonCaptureMoves(board);
    BOOST_CHECK(moves_p2.empty());

    std::vector<Move> moves_p3 = p3.getNonCaptureMoves(board);
    BOOST_CHECK(moves_p3.size() == 2);

    std::vector<Move> moves_p4 = p4.getNonCaptureMoves(board);
    BOOST_REQUIRE(moves_p4.size() == 1);
    BOOST_CHECK( moves_p4[0].getStartPosition() == Position(7,1) );
    BOOST_CHECK( moves_p4[0].getEndPosition() == Position(6,0));
    BOOST_CHECK( moves_p4[0].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p4[0].getStepMoves().empty() );
    BOOST_REQUIRE( moves_p4[0].getUpgradePositions().size() == 1 );
    BOOST_CHECK( moves_p4[0].getUpgradePositions()[0] == Position(6,0));


}

BOOST_AUTO_TEST_CASE(no_capture_moves_king){
    Board board = Board();
    King p1(Position(1,6), true, true, board);
    Pawn p2(Position(4,3), true, true, board);
    King p3(Position(7,0), true, true, board);

    std::vector<Move> moves_p1 = p1.getNonCaptureMoves(board);

    BOOST_REQUIRE (moves_p1.size() == 5);
    BOOST_CHECK( moves_p1[0].getStartPosition() == Position(1,6)  && moves_p1[1].getStartPosition() == Position(1,6) && moves_p1[2].getStartPosition() == Position(1,6)
                                    && moves_p1[3].getStartPosition() == Position(1,6) && moves_p1[4].getStartPosition() == Position(1,6));
    BOOST_CHECK( moves_p1[0].getEndPosition() == Position(2,7));
    BOOST_CHECK( moves_p1[1].getEndPosition() == Position(0,7));
    BOOST_CHECK( moves_p1[2].getEndPosition() == Position(0,5));
    BOOST_CHECK( moves_p1[3].getEndPosition() == Position(2,5));
    BOOST_CHECK( moves_p1[4].getEndPosition() == Position(3,4));
    BOOST_CHECK( moves_p1[0].getCapturedPositions().empty() && moves_p1[1].getCapturedPositions().empty() && 
                                            moves_p1[2].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p1[0].getStepMoves().empty() && moves_p1[1].getStepMoves().empty() && 
                                            moves_p1[2].getStepMoves().empty() );
    BOOST_CHECK( moves_p1[0].getUpgradePositions().empty() && moves_p1[1].getUpgradePositions().empty() && 
                                            moves_p1[2].getUpgradePositions().empty() );

    std::vector<Move> moves_p3 = p3.getNonCaptureMoves(board);

    BOOST_REQUIRE (moves_p3.size() == 2);
    BOOST_CHECK( moves_p3[0].getStartPosition() == Position(7,0)  && moves_p3[1].getStartPosition() == Position(7,0) );
    BOOST_CHECK( moves_p3[0].getEndPosition() == Position(6,1));
    BOOST_CHECK( moves_p3[1].getEndPosition() == Position(5,2));
    BOOST_CHECK( moves_p3[0].getCapturedPositions().empty() && moves_p1[1].getCapturedPositions().empty() && 
                                            moves_p1[2].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p3[0].getStepMoves().empty() && moves_p1[1].getStepMoves().empty() && 
                                            moves_p1[2].getStepMoves().empty() );
    BOOST_CHECK( moves_p3[0].getUpgradePositions().empty() && moves_p1[1].getUpgradePositions().empty() && 
                                            moves_p1[2].getUpgradePositions().empty() );


}

//Player

BOOST_AUTO_TEST_CASE(initilizePieces){
    Board board = Board();
    auto user = UserPlayer(true);
    user.initializePieces(board);

    BOOST_REQUIRE(user.getPieces().size() == 12);
    BOOST_CHECK(user.getPieces()[0]->getPosition() == Position(0,0));
    BOOST_CHECK(board.getPieceName(Position(0,0)) == WHITE_PAWN);

    auto computer = AIPlayer(false);
    computer.initializePieces(board);
    BOOST_REQUIRE(computer.getPieces().size() == 12);
    BOOST_CHECK(computer.getPieces()[11]->getPosition() == Position(7,5));
    BOOST_CHECK(board.getPieceName(Position(7,5)) == BLACK_PAWN);

}

BOOST_AUTO_TEST_CASE(getValidMoves){
    Board board = Board();
    auto user = UserPlayer(true);
    user.addPiece(false, Position(1,1), board);
    user.addPiece(false, Position(3,1), board);
    user.addPiece(false, Position(5,1), board);
    auto computer = AIPlayer(false);
    computer.addPiece(false, Position(2,2), board);
    computer.addPiece(true, Position(4,4), board);

    std::vector<std::vector<Move>> moves_user = user.getValidMoves(board);
    std::vector<std::vector<Move>> moves_computer = computer.getValidMoves(board);

    BOOST_REQUIRE(moves_user.size() == 2);
    BOOST_CHECK(moves_user[0].size() == 1 && moves_user[1].size() == 1);
    BOOST_REQUIRE(moves_computer.size() == 1);
    BOOST_CHECK(moves_computer[0].size() == 3);

    //empty and not capture case
    Board board_2 = Board();
    auto user_2 = UserPlayer(true);
    user_2.addPiece(false, Position(0,0), board_2);
    auto computer_2 = AIPlayer(false);
    computer_2.addPiece(false, Position(1,1), board_2);
    computer_2.addPiece(false, Position(2,2), board_2);

    std::vector<std::vector<Move>> moves_user_2 = user_2.getValidMoves(board_2);
    std::vector<std::vector<Move>> moves_computer_2 = computer_2.getValidMoves(board_2);

    BOOST_REQUIRE(moves_user_2.empty());
    BOOST_REQUIRE(moves_computer_2.size() == 2);
    BOOST_CHECK(moves_computer_2[0].size() == 1 && moves_computer_2[1].size() == 1);
}

BOOST_AUTO_TEST_CASE(movePiece){
    Board board = Board();
    auto user = UserPlayer(true);
    user.addPiece(false, Position(1,5), board);
    auto computer = AIPlayer(false);
    computer.addPiece(false, Position(2,6), board);
    computer.addPiece(false, Position(6,4), board);

    std::vector<std::vector<Move>> moves_user = user.getValidMoves(board);
    BOOST_REQUIRE(moves_user.size() == 1);
    BOOST_REQUIRE(moves_user[0].size() == 1);

    user.movePiece(board, computer, moves_user[0][0]);

    BOOST_CHECK(computer.getPieces().empty());
    BOOST_REQUIRE(user.getPieces().size() == 1);
    BOOST_CHECK(user.getPieces()[0]->getPosition() == Position(7,3));
    BOOST_CHECK(board.getPieceName(Position(7,3)) == WHITE_KING);
}

BOOST_AUTO_TEST_CASE(checkersInit) {
    std::string initWhite = "1p1p1p1p/p1p1p1p1/1p1p1p1p/8/8/P1P1P1P1/1P1P1P1P/P1P1P1P1";
    std::string initBlack = "1P1P1P1P/P1P1P1P1/1P1P1P1P/8/8/p1p1p1p1/1p1p1p1p/p1p1p1p1";
    auto ch = Checkers::getInstance();
    ch.initialize("Adam", false);
    BOOST_REQUIRE(ch.getGameState().boardFEN == initBlack);
    BOOST_CHECK(ch.getGameState().userName == "Adam" );
    ch.initialize("Bartek", true);
    BOOST_REQUIRE(ch.getGameState().boardFEN == initWhite);

    ch.fenInitialize("8/2k5/8/4p3/8/2P3P1/8/4K3", "Jim", true, true);
    BOOST_CHECK(ch.getGameState().boardFEN == "8/2k5/8/4p3/8/2P3P1/8/4K3");
}

BOOST_AUTO_TEST_CASE(checkersGame) {
    std::string initWhite = "1p1p1p1p/p1p1p1p1/1p1p1p1p/8/8/P1P1P1P1/1P1P1P1P/P1P1P1P1";
    std::string initBlack = "1P1P1P1P/P1P1P1P1/1P1P1P1P/8/8/p1p1p1p1/1p1p1p1p/p1p1p1p1";

    auto ch = Checkers::getInstance();
    ch.initialize("Patrycja", true);
    // computer move not in its turn
    auto state = ch.makeComputerMove();
    BOOST_REQUIRE( state.boardFEN == initWhite);
    // wrong user move
    state = ch.processUserMove("c3", "e5");
    BOOST_REQUIRE( state.boardFEN == initWhite);
    state = ch.processUserMove("a1", "b2");
    BOOST_REQUIRE( state.boardFEN == initWhite);
    // good move
    state = ch.processUserMove("c3", "d4");
    BOOST_REQUIRE( state.boardFEN == "1p1p1p1p/p1p1p1p1/1p1p1p1p/8/3P4/P3P1P1/1P1P1P1P/P1P1P1P1");
    state = ch.makeComputerMove();
    BOOST_REQUIRE(state.boardFEN != "1p1p1p1p/p1p1p1p1/1p1p1p1p/8/3P4/P3P1P1/1P1P1P1P/P1P1P1P1");
}

BOOST_AUTO_TEST_CASE(multipleCaptureUser) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("8/8/3p3K/8/3p4/2P5/8/8", "Adam", true, true);
    auto state = ch.processUserMove("c3", "e5");
    BOOST_CHECK(state.boardFEN == "8/8/3p3K/4P3/8/8/8/8");
    BOOST_REQUIRE( state.isUserTurn && state.isInMultipleMove);
    BOOST_REQUIRE( state.score == Score::IN_PROGRESS);
    state = ch.processUserMove("e5", "c7");
    BOOST_CHECK( state.boardFEN == "8/2P5/7K/8/8/8/8/8");
    BOOST_CHECK( !state.isUserTurn && !state.isInMultipleMove);
}

BOOST_AUTO_TEST_CASE(multipleCaptureComputer) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("8/8/3p3K/8/3p4/2P5/8/8", "Adam", false, false);
    auto state = ch.makeComputerMove();
    BOOST_CHECK(state.boardFEN == "8/2P5/7K/8/8/8/8/8");
    BOOST_CHECK(state.isUserTurn && !state.isInMultipleMove);

    // triple move with king
    ch.fenInitialize("8/2P3K1/5p2/8/3p4/8/3p4/8", "Walter White", false, false);
    state = ch.makeComputerMove();
    BOOST_CHECK(state.boardFEN == "8/2P5/8/8/8/8/8/4K3");
}

BOOST_AUTO_TEST_CASE(upgradeToKingUser) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("8/4P3/1p6/8/8/8/8/8", "Willy Wonka", true, true);
    auto state = ch.processUserMove("e7", "d8");
    BOOST_REQUIRE( state.boardFEN == "3K4/8/1p6/8/8/8/8/8");
    BOOST_CHECK( !state.isUserTurn );
    
    ch.fenInitialize("8/4p3/1p3P2/8/8/8/8/8", "Barte", true, true);
    state = ch.processUserMove("f6", "d8");
    BOOST_REQUIRE( state.boardFEN == "3K4/8/1p6/8/8/8/8/8");
    BOOST_CHECK( state.isUserTurn && state.isInMultipleMove );
    state = ch.processUserMove("d8", "a5");
    BOOST_REQUIRE( state.boardFEN == "8/8/8/K7/8/8/8/8");
    BOOST_CHECK( !state.isUserTurn );
}

BOOST_AUTO_TEST_CASE(upgradeToKingComputer) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("8/8/8/8/5p2/P7/1p6/8", "Mark", false, false);
    auto state = ch.makeComputerMove();
    BOOST_REQUIRE( state.boardFEN == "8/8/8/6K1/8/8/8/8" || state.boardFEN == "8/8/7K/8/8/8/8/8");
}

BOOST_AUTO_TEST_CASE(drawEnd) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("5k2/8/8/8/8/8/8/2K5", "Waldek", true, true);
    std::vector<std::string> userSpots = {"c1", "d2"};
    for (int i = 0; i < 15; ++i) {
        ch.processUserMove(userSpots.at(i % 2), userSpots.at(std::abs(i % 2 - 1)));
        ch.makeComputerMove();
    }
    auto state = ch.getGameState();
    BOOST_REQUIRE( state.hasGameEnded && state.score == Score::DRAW);
}

BOOST_AUTO_TEST_CASE(userWonEnd) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("8/8/3P4/4p3/8/8/8/8", "asdf", true, true);
    auto state = ch.processUserMove("d6", "f4");
    BOOST_REQUIRE( state.hasGameEnded && state.score == Score::USER_WON);
}

BOOST_AUTO_TEST_CASE(userLostEnd) {
    auto ch = Checkers::getInstance();
    ch.fenInitialize("3p4/4K3/8/4P3/8/8/8/8", "asdfghjk", true, false);
    auto state = ch.makeComputerMove();
    BOOST_REQUIRE( state.hasGameEnded && state.score == Score::USER_LOST);
}


BOOST_AUTO_TEST_SUITE_END()