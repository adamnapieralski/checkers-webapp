#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>

struct Position {
    int x, y;
    Position() : x(0), y(0) {};
    Position(int setX, int setY) : x(setX), y(setY) {};

    bool isPositionValid() {
        if (x >= 0 && x <= 8 && y >=0 && y <=8) return true;
        else return false;
    }

    bool operator==(Position &p) {
        if (x == p.x && y == p.y) return true;
        else return false;
    }

    bool operator!=(Position &p) {
        if (x != p.x || y != p.y) return true;
        else return false;
    }
};


enum PieceName {
    Empty, WhiteKing, WhitePawn, BlackKing, BlackPawn
};

inline std::ostream& operator<<(std::ostream& os, const PieceName& p){
    switch (p){
        case Empty : os << "_"; break;
        case WhiteKing : os << "wK"; break ;
        case WhitePawn : os << "w"; break;
        case BlackKing : os << "bK"; break ;
        case BlackPawn : os << "b"; break ;
        default : os << " "; break ;
    }
    return os;
}

#endif // POSITION_HPP
