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
    auto newComp = computer.getPieces();
    auto newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 0);
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(6,4);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WHITE_KING);

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

    auto newComp = computer.getPieces();
    auto newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 1 || newComp.size() == 2 );
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(0,0);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WHITE_PAWN);

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

    auto newComp = computer.getPieces();
    auto newUs = user.getPieces();

    BOOST_CHECK(newComp.size() == 1);
    BOOST_CHECK(newUs.size() == 1);

    Position rPos(0,0);

    BOOST_CHECK(newUs[0]->getPosition() == rPos);
    BOOST_CHECK(board.getPieceName(rPos) == WHITE_KING);

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

    board.placePiece(Position(0, 0), WHITE_KING);
    board.placePiece(Position(4, 4), BLACK_KING);
    board.placePiece(Position(2, 6), WHITE_KING);
    board.placePiece(Position(7, 7), BLACK_KING);
    board.placePiece(Position(5, 3), WHITE_KING);
    BOOST_CHECK( board.getFEN() == "1P1P1P1K/P1k1P1P1/1P1P1P1P/4K3/5k2/p1p1p1p1/1p1p1p1p/k1p1p1p1" );
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
    BOOST_REQUIRE( move_a.getChangedPosition().size() == 1 );
    BOOST_CHECK (move_a.getChangedPosition()[0] == Position(3,7));

    Move move_b = moves_b[0];

    BOOST_CHECK( move_b.getStartPosition() == Position(2,6) );
    BOOST_CHECK( move_b.getEndPosition() == Position(0,4));
    BOOST_REQUIRE( move_b.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_b.getCapturedPositions()[0] == Position(1,5));
    BOOST_CHECK( move_b.getStepMoves().empty());
    BOOST_CHECK( move_b.getChangedPosition().empty());

    
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
    BOOST_CHECK( move_a.getChangedPosition().empty() );

    Move move_b = moves_b[0];

    BOOST_CHECK( move_b.getStartPosition() == Position(2,5) );
    BOOST_CHECK( move_b.getEndPosition() == Position(0,3));
    BOOST_REQUIRE( move_b.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_b.getCapturedPositions()[0] == Position(1,4));
    BOOST_CHECK( move_b.getStepMoves().empty());
    BOOST_CHECK( move_b.getChangedPosition().empty());

    
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
    BOOST_CHECK( move_b_0.getChangedPosition().empty());

    Move move_b_1 = moves_b[1];

    BOOST_CHECK( move_b_1.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_1.getEndPosition() == Position(0,0));
    BOOST_REQUIRE( move_b_1.getCapturedPositions().size() == 1 );
    BOOST_CHECK( move_b_1.getCapturedPositions()[0] == Position(1,1) );
    BOOST_CHECK( move_b_1.getStepMoves().empty() );
    BOOST_CHECK( move_b_1.getChangedPosition().empty());

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

    std::cout << moves_b.size() <<std::endl;
    BOOST_REQUIRE(moves_b.size() == 11);
    
    Move move_b_0 = moves_b[0];

    BOOST_CHECK( move_b_0.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_0.getEndPosition() == Position(0,0));
    BOOST_REQUIRE( move_b_0.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_0.getCapturedPositions()[0] == Position(3,3) && move_b_0.getCapturedPositions()[1] == Position(1,1) );
    BOOST_CHECK( move_b_0.getStepMoves().size() == 2 );
    BOOST_CHECK (move_b_0.getChangedPosition().empty());

    Move step_b_0 =  move_b_0.getStepMoves()[0];
    BOOST_CHECK( step_b_0.getStartPosition() == Position(2,2) );
    BOOST_CHECK( step_b_0.getEndPosition() == Position(4,4));
    BOOST_REQUIRE( step_b_0.getCapturedPositions().size() == 1 );
    BOOST_CHECK( step_b_0.getCapturedPositions()[0] == Position(3,3) );
    BOOST_CHECK( step_b_0.getStepMoves().empty() );
    BOOST_CHECK (step_b_0.getChangedPosition().empty());

    Move move_b_1 = moves_b[8];

    BOOST_CHECK( move_b_1.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_1.getEndPosition() == Position(5,5));
    BOOST_REQUIRE( move_b_1.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_1.getCapturedPositions()[0] == Position(1,1) &&  move_b_1.getCapturedPositions()[1] == Position(3,3));
    BOOST_CHECK( move_b_1.getStepMoves().size() == 2);
    BOOST_CHECK (move_b_0.getChangedPosition().empty());


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
    BOOST_REQUIRE( move_b_0.getChangedPosition().size() == 1);
    BOOST_CHECK (move_b_0.getChangedPosition()[0] == Position(0,0));

    Move move_b_1 = moves_b[4];

    BOOST_CHECK( move_b_1.getStartPosition() == Position(2,2) );
    BOOST_CHECK( move_b_1.getEndPosition() == Position(6,6));
    BOOST_REQUIRE( move_b_1.getCapturedPositions().size() == 2 );
    BOOST_CHECK( move_b_1.getCapturedPositions()[0] == Position(1,1) &&  move_b_1.getCapturedPositions()[1] == Position(3,3));
    BOOST_CHECK( move_b_1.getStepMoves().size() == 2);
    BOOST_REQUIRE( move_b_0.getChangedPosition().size() == 1);
    BOOST_CHECK (move_b_0.getChangedPosition()[0] == Position(0,0));

}

BOOST_AUTO_TEST_CASE(no_capture_moves_pawn){
    Board board = Board();
    Pawn p1(Position(1,1), true, true, board);
    Pawn p2(Position(0,0), true, true, board);
    Pawn p3(Position(2,2), true, true, board);
    Pawn p4(Position(7,1), false, false, board);

    std::vector<Move> moves_p1 = p1.getValidMoves(board);

    BOOST_REQUIRE (moves_p1.size() == 1);
    BOOST_CHECK( moves_p1[0].getStartPosition() == Position(1,1) );
    BOOST_CHECK( moves_p1[0].getEndPosition() == Position(0,2));
    BOOST_CHECK( moves_p1[0].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p1[0].getStepMoves().empty() );
    BOOST_CHECK( moves_p1[0].getChangedPosition().empty() );

    std::vector<Move> moves_p2 = p2.getValidMoves(board);
    BOOST_CHECK(moves_p2.empty());

    std::vector<Move> moves_p3 = p3.getValidMoves(board);
    BOOST_CHECK(moves_p3.size() == 2);

    std::vector<Move> moves_p4 = p4.getValidMoves(board);
    BOOST_REQUIRE(moves_p4.size() == 1);
    BOOST_CHECK( moves_p4[0].getStartPosition() == Position(7,1) );
    BOOST_CHECK( moves_p4[0].getEndPosition() == Position(6,0));
    BOOST_CHECK( moves_p4[0].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p4[0].getStepMoves().empty() );
    BOOST_REQUIRE( moves_p4[0].getChangedPosition().size() == 1 );
    BOOST_CHECK( moves_p4[0].getChangedPosition()[0] == Position(6,0));


}

BOOST_AUTO_TEST_CASE(no_capture_moves_king){
    Board board = Board();
    King p1(Position(1,6), true, true, board);
    Pawn p2(Position(4,3), true, true, board);
    King p3(Position(7,0), true, true, board);

    std::vector<Move> moves_p1 = p1.getValidMoves(board);

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
    BOOST_CHECK( moves_p1[0].getChangedPosition().empty() && moves_p1[1].getChangedPosition().empty() && 
                                            moves_p1[2].getChangedPosition().empty() );

    std::vector<Move> moves_p3 = p3.getValidMoves(board);

    BOOST_REQUIRE (moves_p3.size() == 2);
    BOOST_CHECK( moves_p3[0].getStartPosition() == Position(7,0)  && moves_p3[1].getStartPosition() == Position(7,0) );
    BOOST_CHECK( moves_p3[0].getEndPosition() == Position(6,1));
    BOOST_CHECK( moves_p3[1].getEndPosition() == Position(5,2));
    BOOST_CHECK( moves_p3[0].getCapturedPositions().empty() && moves_p1[1].getCapturedPositions().empty() && 
                                            moves_p1[2].getCapturedPositions().empty() );
    BOOST_CHECK( moves_p3[0].getStepMoves().empty() && moves_p1[1].getStepMoves().empty() && 
                                            moves_p1[2].getStepMoves().empty() );
    BOOST_CHECK( moves_p3[0].getChangedPosition().empty() && moves_p1[1].getChangedPosition().empty() && 
                                            moves_p1[2].getChangedPosition().empty() );


}

//Player

BOOST_AUTO_TEST_CASE(initilizePieces){
    Board board = Board();
    Player user = Player(&board, true, true);
    user.initializePieces();

    BOOST_REQUIRE(user.getPieces().size() == 12);
    BOOST_CHECK(user.getPieces()[0]->getPosition() == Position(0,0));
    BOOST_CHECK(board.getPieceName(Position(0,0)) == WHITE_PAWN);

    Player computer = Player(&board, false, false);
    computer.initializePieces();
    BOOST_REQUIRE(computer.getPieces().size() == 12);
    BOOST_CHECK(computer.getPieces()[11]->getPosition() == Position(7,5));
    BOOST_CHECK(board.getPieceName(Position(7,5)) == BLACK_PAWN);

}


BOOST_AUTO_TEST_SUITE_END()