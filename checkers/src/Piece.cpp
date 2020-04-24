/**
 * Projekt Zaawansowane Programowanie w C++ - Warcaby
 * 24.04.2020
 * 
 * Autorzy: Patrycja Cieplicka, Adam Napieralski
 * 
 * Plik źródłowy klasy abstrakcyjnej Piece, która reprezntuje wszystkie figury warcabowe
 * 
 * */


#include "Piece.hpp"
#include "Pawn.hpp"
#include "King.hpp"
#include "Board.hpp"

// Piece::Piece(Position pos, bool isWhite) {
//     pos_ = pos;
//     isWhite_ = isWhite;
// }

Piece::Piece(Position pos, bool isWhite, bool isUser) :
    pos_(pos), isWhite_(isWhite), isUser_(isUser) {}

bool Piece::isWhite() const { return isWhite_;    }

bool Piece::isUser() const {  return isUser_; }

Position Piece::getPosition() const { return pos_;    }

void Piece::changePosition(Position pos){
    pos_ = pos;
}

bool Piece::isSameColor(PieceName &pn) const {
    if ( (isWhite_ && ( pn == WHITE_PAWN  || pn == WHITE_KING ) )
        || (!isWhite_ && (pn == BLACK_PAWN || pn == BLACK_KING) ) )
        return true;
    else return false;
}

bool Piece::isDiffColor(PieceName pn) const{
    if ( (isWhite_ && ( pn == BLACK_PAWN || pn == BLACK_KING) )
        || (!isWhite_ && (pn == WHITE_PAWN || pn == WHITE_KING) ) )
        return true;
    else return false;
}
