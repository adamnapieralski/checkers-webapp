#include "King.hpp"

std::ostream& King::print(std::ostream& os){
    if (this->isWhite()) os << "K";
    else os << "B";
    return os;
}