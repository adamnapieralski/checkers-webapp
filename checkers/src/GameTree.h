/**
 * @file GameTree.h
 * @brief Header file for GameTree class, representing the game tree for minimax alfa beta algorithm.
 * 
 * @author Patrycja Cieplicka
 * @author Adam Napieralski
 */

#ifndef GAMETREE_H
#define GAMETREE_H

#include <memory>
#include "Board.h"

struct TNode {
    TNode(Move m, Board b) : move_(m), board_(b){}
    TNode(Board b) : board_(b){}
    ~TNode() {};

    Move move_;
    Board board_;
    std::shared_ptr<TNode> parent_;              
    std::vector<std::shared_ptr<TNode>> children_;
};


class GameTree {

public:
    GameTree(Board b);
    void addChildren(Move m, Board b);
    void changeCurrentHeadToParent();

private:
    std::shared_ptr<TNode> root_;
    std::weak_ptr<TNode> currentHead_;

};



#endif // GAMETREE_H