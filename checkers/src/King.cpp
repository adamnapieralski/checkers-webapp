#include "King.hpp"

std::vector<Move> King::getValidMoves(Board& board) {
    Position startPos = getPosition();
    std::vector<std::vector<Position>> newPosDir(4, std::vector<Position>{});
    std::vector<Move> moves;
    int r[4] = {1, 1, -1, -1};
    int c[4] = {1, -1, -1, 1};
    std::vector<std::pair<bool, Position>> captured(4, std::pair<bool, Position>(false, Position()));
    bool canCapture = false;
    // populate with all valid diagonal positions
    for (int i = 0; i < 4; ++i) {
        bool metOpponent = false;
        Position p(startPos.x + c[i], startPos.y + r[i]);
        while (p.isPositionValid()) {
            PieceName pn = board.getPieceName(p);
            if (isSameColor(pn))  break;
            if (metOpponent && pn == Empty && !captured[i].first) {
                canCapture = true;
                captured[i].first = true;
                newPosDir[i].clear();
            }
            if (isDiffColor(pn)) {
                if (metOpponent) break;
                else{
                    metOpponent = true;
                    captured[i].second = p;
                }
            }
            else {
                newPosDir[i].push_back(p);
            }
            p.x += c[i];
            p.y += r[i];
        }
    }
    if (canCapture) {
        for (int i = 0; i < captured.size(); ++i) {
            if (captured[i].first) {
                for (auto& pos : newPosDir[i])
                    Move m(startPos, pos, captured[i].second);
                    // moves.push_back(Move(startPos, pos, captured[i].second));
            }
        }
    }
    else {
        for (auto& dir : newPosDir) {
            for (auto& pos : dir) {
                moves.push_back(Move(startPos, pos));
            }
        }
    }

    return moves; // temp
}

bool King::canCapture(Piece& piece, Board &board) {
    if (this->isWhite() == piece.isWhite()) return false;
    // if not on same diagonal
    if (isOnSameDiagonal(piece)) return false;

    Position diff = positionDistance(piece);
    Position thisPos = this->getPosition(), piecePos = piece.getPosition();

    int stepX = diff.x / abs(diff.x), stepY = diff.y / abs(diff.y);
    for (int i = 1; i < abs(diff.x); ++i) {
        if (board.getBoard()[thisPos.x + i * stepX][thisPos.y + i * stepY] != Empty)
            return false;
    }

    int newX = piecePos.x + stepX;
    int newY = piecePos.y + stepY;
    Position newPos(newX, newY);

    if (!newPos.isPositionValid()) return false;
    if (board.getBoard()[newX][newY] == Empty) return true;
    else return false;
}


std::ostream& King::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}
