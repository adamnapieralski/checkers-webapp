#include "Pawn.hpp"

std::ostream& Pawn::print(std::ostream& os){
    if (this->isWhite()) os << "w";
    else os << "b";
    return os;
}
