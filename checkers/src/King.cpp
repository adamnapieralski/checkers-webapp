#include "King.hpp"

King::King(Position pos, bool isWhite, bool isUser, Board& board) : Piece(pos, isWhite, isUser) {
    if (isWhite)
        board.placePiece(pos, WhiteKing);
    else
        board.placePiece(pos, BlackKing);
}

std::vector<Move> King::getValidMoves(Board& board, bool mustCapture) {
    std::vector<Move> moves;

    Position startPos = getPosition();

    std::vector<std::vector<Position>> newPosDiag(4, std::vector<Position>{});
    std::vector<std::pair<bool, Position>> captured(4, std::pair<bool, Position>(false, Position()));
    
    bool canCapture = false;
    int dy[4] = {1, 1, -1, -1};
    int dx[4] = {1, -1, -1, 1};

    // populate with all valid diagonal positions
    for (int i = 0; i < 4; ++i) {
        bool metOpponent = false;
        Position p(startPos.x + dx[i], startPos.y + dy[i]);
        while (p.isValid()) {
            PieceName pn = board.getPieceName(p);
            if (isSameColor(pn))  break;
            if (metOpponent && pn == Empty && !captured[i].first) {
                canCapture = true;
                captured[i].first = true;
                newPosDiag[i].clear();
            }
            if (isDiffColor(pn)) {
                if (metOpponent) break;
                else{
                    metOpponent = true;
                    captured[i].second = p;
                }
            }
            else {
                newPosDiag[i].push_back(p);
            }
            p.x += dx[i];
            p.y += dy[i];
        }
    }
    if (canCapture) {
        for (int i = 0; i < captured.size(); ++i) {
            if (captured[i].first) {
                for (auto& pos : newPosDiag[i]) {
                    Move m(startPos, pos, captured[i].second);
                    auto tempBoard = board;
                    tempBoard.makeMove(m);
                    King k(pos, isWhite(), isUser(), tempBoard);

                    auto nextMoves = k.getValidMoves(tempBoard, true);
                    if (nextMoves.empty()) {
                        moves.push_back(m);
                    }
                    else {
                        for (auto& nm : nextMoves) {
                            moves.push_back(m.merge(nm));
                        }
                    }
                }
            }
        }
    }
    else if (!mustCapture) {
        for (auto& dg : newPosDiag) {
            for (auto& pos : dg) {
                moves.push_back(Move(startPos, pos));
            }
        }
    }
    return moves;
}

void King::canCapture(std::vector<Move> &moves, Board board, Move current) {};


// bool King::canCapture(Piece& piece, Board &board) {
//     if (this->isWhite() == piece.isWhite()) return false;
//     // if not on same diagonal
//     if (isOnSameDiagonal(piece)) return false;

//     Position diff = positionDistance(piece);
//     Position thisPos = this->getPosition(), piecePos = piece.getPosition();

//     int stepX = diff.x / abs(diff.x), stepY = diff.y / abs(diff.y);
//     for (int i = 1; i < abs(diff.x); ++i) {
//         if (board.getBoard()[thisPos.x + i * stepX][thisPos.y + i * stepY] != Empty)
//             return false;
//     }

//     int newX = piecePos.x + stepX;
//     int newY = piecePos.y + stepY;
//     Position newPos(newX, newY);

//     if (!newPos.isValid()) return false;
//     if (board.getBoard()[newX][newY] == Empty) return true;
//     else return false;
// }


std::ostream& King::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}
