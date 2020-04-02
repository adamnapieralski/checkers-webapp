#include "Board.hpp"

Board::Board(){
    board_={ {
    { { BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty } },
    { { Empty, BlackPawn, Empty, BlackPawn, Empty,BlackPawn , Empty, BlackPawn } },
    { { BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty, BlackPawn, Empty } },
    { { Empty, Empty, Empty, Empty, Empty, Empty, Empty,Empty } },
    { { Empty, Empty, Empty, Empty, Empty, Empty, Empty,Empty } },
    { { WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty } },
    { { Empty, WhitePawn, Empty, WhitePawn, Empty, WhitePawn ,Empty, WhitePawn } },
    { { WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty, WhitePawn, Empty } },
    } };
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    for(auto i = b.board_.begin(); i != b.board_.end(); ++i ){
        for(auto j = (*i).begin(); j != (*i).end(); ++j ){
            std::cout << *j << " ";
        }
        std::cout << std::endl;
    }
    return os;
}
